/******
 * this file is for api reference, not compiling
 */

lua_State *L;

/***** 24.2 -- the stack (cf. stack_demo.c) **/

/**
 * 24.2.1 pushing elements
 */

// all the following return void
lua_pushnil(L);
int bool;
lua_pushboolean(L, bool);
double n;
lua_pushnumber(L, n);
size_t str_len = 256; // ?? where's size_t defined, again?
/* recall that '\0' is appended to the array by the C language
 * for string literals
 */
char some_str[str_len] = "asdf";
// this is the official function for pushing strings
lua_pushlstring(L, some_str, str_len);
// some_str must end with '\0' for this convenience function
lua_pushstring(L, some_str);
/* lua strings are _not_ zero-terminated:  these functions
 * copy the strings pointed at by `char *` to a different
 * memory space, so some_str can be modified w/o changing the stack
 */

/*
 * this section mentions checking for free space on the stack
 * as an afterthought-ish
 */
// ??? number of spaces in stack?  bytes?
int size;
// guessing at the semantics (bool) of int return value
int is_space = lua_checkstack(L, size);
printf("lua minimum stack size: %d\n", LUA_MINSTACK);

/**
 * 24.2.2 querying elements
 */

/*
 * on indexing:
 *  - positive integers refer to elements in the order they pushed,
 *    with lower values meaning elements that were pushed earlier
 *  - negative integers refer to elements from top of the stack,
 *    so -1 is the most recently pushed element
 */

int typecheck_bool = lua_isnumber(L, -1);
lua_isstring(L, -1);
lua_istable(L, -1);
//... and lua_is* for all lua types
/*
 * these check whether the value __can be converted__ to
 * the specified type --- so numbers return truthy values for
 *  lua_isstring, for instance
 */
switch (lua_type(L, -1)) {
 case LUA_TNIL:
   break;
 case LUA_TBOOLEAN:
   break;
 case LUA_TNUMBER:
   break;
 case LUA_TSTRING:
   break;
 case LUA_TTABLE:
   break;
 case LUA_TFUNCTION:
   break;
 case LUA_TUSERDATA:
   break;
 case LUA_TTHREAD:
   break;
 default:
 }

/*
 * and returning values from the stack:
 * - even if the idx doesn't have the correct type,
 *   a value is returned NULL or 0, denoted (ret_val) below
 */
int ret_bool = lua_toboolean(L, -1); // (NULL)
double ret_number = lua_tonumber(L, -1); // (0)
size_t len_ret_string = lua_strlen(L, -1); // (0)
/*
 * - this is a pointer to internal copy of the string
 *   used by the interpreter
 * - it _is_ '\0'-terminated, although '\0' may occur else
 *   in the string, so lua_strlen is helpful to be certain
 */
const char *ret_string = lua_tostring(L, -1); // (NULL)
// ... and this is the complete list of stack value getters

/**
 * 24.2.3 other stack functions
 */

/**
 * number of elements in stack (aka index of top of stack)
 */
int num_elems = lua_gettop(L);

//// the following functions return void /

/**
 * ensures that there are precisely as many elements in the
 * stack as specified,
 * - discarding elements if there are currently more elements
 *   than specified
 * - adding `nil` to the stack if fewer
 */
// clears the stack entirely
lua_settop(L, 0);
// no-op
lua_settop(L, -1);

/**
 * actually a macro:
 * lua_pop(L, n) -> lua_settop(L, -(n)-1)
 */
lua_pop(L, 1);

/**
 * copies value at the specified index and pushes it
 * onto the top of the stack
 */
 // pushes copy of bottom of the stack onto the top
lua_pushvalue(L, 1);
 // adds an extra copy of the top of the stack to the top
lua_pushvalue(L, -1);

/**
 * removes element at given index, shifting all elements down
 */
// removes first (bottom) element
lua_remove(L, 1);
// same as lua_pop(L, 1)
lua_remove(L, -1);

/**
 * moves top element of the stack to specified position,
 * shifting all elements with greater indexes up by one
 */
// moves top element to bottom, shifting all other elems' index up 1
lua_insert(L, 1);
// no-op
lua_insert(L, -1);

/**
 * pops top and replaces given index with that value
 */
// moves top element to bottom, discarding previous bottom elem,
// and affecting no other stack indices
lua_replace(L, 1);

/******
 *  27 -- techniques for writing C functions
 ******/

/**
 * 27.1 array manipulation
 *
 * recall that lua has no 'array' type.  rather, arrays
 * are tables *used* in a particular way. for example, see
 * - literally_tables.lua
 * - iter.lua
 * and to a lesser degree
 * - coro.lua
 * in the parent directory.
 *
 * at the C api level, however, there is a pair of special
 * functions for handling arrays.
 */


/*
 * `index` -- stack index (as above)
 * `key` -- array index
 *
 * the reason these functions are "special", then,
 * derives in part from C's type system:  there could
 * probably be a tagged union (i.e. a struct) passed in
 * for `key`.  however, when indexing arrays, the usual
 * idea is to optimize for speed.
 */
void lua_rawgeti(lua_State *L, int index, int key);
void lua_rawseti(lua_State *L, int index, int key);

/*
 * lua_rawget and lua_rawset (non-"i for indexed" versions
 * of the above) are just like lua_gettable and lua_settable,
 * except they disregard any metamethods (see `meta_set.lua`
 * in the parent directory).
 *
 * with that understood, these "totally new" C api functions
 * desugar to something like
 */

void lua_rawgeti(lua_State *L, int index, int key) {
  lua_pushnumber(L, key);
  if (index > 1) {
    lua_rawget(L, index);
  } else {
    // account for additional element on the stack
    lua_rawget(L, index - 1);
  }
}

void lua_rawseti(lua_State *L, int index, int key) {
  lua_pushnumber(L, key);
  /*
   * value to insert is initially at top of the stack for both
   * `lua_rawset` and `lua_rawseti`, so for `lua_rawset`, the index
   * needs to be shuffled to the next-to-top stack position
   */
  lua_insert(L, -2);
  if (index > 1) {
    lua_rawset(L, index);
  } else {
    // account for additional element on the stack
    lua_rawset(L, index - 1);
  }
}

/*
 * in other words (since the metatable stuff usually doesn't
 * occur in lua scripts that need arrays processed really fast
 * in C),
 * - lua_rawgeti takes an index of a table on the stack
 *   and an index of an element in the table and puts
 *   the element it finds there at the top of the stack
 *
 * - lua_rawseti takes similar arguments and places an element
 *   from the top of the stack in the specified position,
 *   popping it off the top of the stack
 */

/**
 * 27.2 -- strings
 *
 * accessing strings created by lua in the stack accessible
 * via the C api does require some care.  the reverse direction,
 * creating strings in C and proving them to lua, is more the
 * rub of this section.
 */

/*
 * use the lua api for slicing, kinda like `string.sub(my_str, i, j)`
 * the first param is ptr arithmetic, the second a length calculation
 */
lua_pushlstring(L, my_str+i, (j-i) + 1);

