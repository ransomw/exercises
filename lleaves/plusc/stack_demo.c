#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "my_lua_utils.h"

/***** 24.2 -- the stack **/

/**
 * 24.2.1 pushing elements
 */
static void pushing (lua_State *L) {
  int bool_false = 0;
  double some_number = 1.41;
  /*
   * recall size_t a system-specific unsigned int typedef
   * from <stddef.h> corresponding to rv of sizeof() operator
   */
  size_t substr_len = 3;
  /*
   * recall that '\0' is appended to the array by the C language
   * for string literals
   */
  char some_str[] = "asdf";
  // all lua_push* functions return void
  lua_pushboolean(L, bool_false);
  // any non-zero is true
  lua_pushboolean(L, -1);
  lua_pushboolean(L, 100);
  lua_pushnil(L);
  lua_pushnumber(L, some_number);
  lua_pushstring(L, some_str);
  lua_pushnil(L);
  lua_pushlstring(L, some_str, 4); // "asdf"
  lua_pushlstring(L, some_str, 10); // "asdf"
  lua_pushlstring(L, some_str, substr_len); // "asd"
}

/**
 * to prevent errors while pushing, check the stack size
 */
static void stack_size_stuffs (lua_State *L) {
  int size_sm = 10;
  int size_med = 1000;
  int size_lrg = 100000;
  int is_space_sm = lua_checkstack(L, size_sm);
  int is_space_med = lua_checkstack(L, size_med);
  int is_space_lrg = lua_checkstack(L, size_lrg);
  printf("lua minimum stack size: %d\n", LUA_MINSTACK);
  printf("lua_checkstack results: %d (sm), %d (med), %d (lrg)\n",
         is_space_sm, is_space_med, is_space_lrg);
  // 1, 1, 0 on my system:  there are about 1000 slots,
  // but not 10,000
}

/**
 * 24.2.2 querying elements
 */
static void querying (lua_State *L) {
  lua_pushnumber(L, 0);
  printf(("the number zero lua_is(*)... "
          "%d (string) " // yes, b/c it can be _coerced_ to a string
          "%d (number) " // claro
          "%d (table) " // nope
          "\n"),
         lua_isstring(L, -1),
         lua_isnumber(L, -1),
         lua_istable(L, -1)
         );
  //... and lua_is* for all lua types.
  printf("... converts a a string as '%s' with length %d ...\n",
         lua_tostring(L, -1),
         lua_strlen(L, -1));
  // note, in particular, than the '\0' is omitted from the strlen
  // (i.e. '0' has length 1)
  // even though values returned by _tostring are '\0'-terminated

  // if it's necessary to see the actual type rather than coerced
  // values, check the implementation of
  printf("... but it still registers with type '%s'.\n",
         get_lua_type_str(L, -1));
  //     ^ this function (in my_lua_utils.c)
  //       contains a list of lua types
  //       with names corresponding to lua_is*

  // .......... could demo more ....
  /*
   * more on returning values from the stack:
   * - even if the idx doesn't have the correct type,
   *   a value is returned NULL or 0, denoted (ret_val) below
   */
  int ret_bool = lua_toboolean(L, -1); // (NULL)
  double ret_number = lua_tonumber(L, -1); // (0)
  size_t len_ret_string = lua_strlen(L, -1); // (0)
  /*
   * this is a pointer to internal copy of the string
   * used by the interpreter
   */
  const char *ret_string = lua_tostring(L, -1); // (NULL)
}

/**
 * 24.2.3 other stack functions
 */
static void more_stack_stuffs (lua_State *L) {
  // number of elements in stack (aka index of top of stack)
  int num_elems = lua_gettop(L);
  pushing(L);
  printf("current stack\n");
  lua_settop(L, -5);
  dump_stack(L);
  // no-op
  lua_settop(L, -1);
  printf("and this ought be the same thing\n");
  dump_stack(L);
  printf("add two nils to the top\n");
  num_elems = lua_gettop(L);
  lua_settop(L, num_elems + 2);
  dump_stack(L);
  printf("remove them\n");
  /*
   * actually a macro:
   * lua_pop(L, n) -> lua_settop(L, -(n)-1)
   */
  lua_pop(L, 2);
  dump_stack(L);
  printf("push value(s)\n");
  /*
   * copies value at the specified index and pushes it
   * onto the top of the stack
   */
  lua_pushvalue(L, -2);
  dump_stack(L);
  printf("remove value(s)\n");
  /*
   * removes element at given index, shifting all elements down
   */
  // same as lua_pop(L, 1)
  lua_remove(L, -1);
  lua_remove(L, 2);
  dump_stack(L);
  printf("insert value(s)\n");
  /*
   * moves top element of the stack to specified position,
   * shifting all elements with greater indexes up by one
   */
  // moves top element to bottom, shifting all other elems' index up 1
  lua_insert(L, 1);
  dump_stack(L);
  printf("replace value(s)\n");
  /*
   * pops top and replaces given index with that value
   */
  // moves top element to bottom, discarding previous bottom elem,
  // and affecting no other stack indices
  lua_replace(L, 1);
  dump_stack(L);
}

int main (void) {
  lua_State *L = lua_open();
  printf("---- stack after lua_open()\n");
  dump_stack(L);
  pushing(L);
  printf("---- stack after pushing()\n");
  dump_stack(L);
  // clears the stack entirely
  lua_settop(L, 0);
  printf("---- stack size stuffs\n");
  stack_size_stuffs(L);
  lua_settop(L, 0);
  printf("---- inquiries re. querying\n");
  querying(L);
  lua_settop(L, 0);
  printf("---- misc.\n");
  more_stack_stuffs(L);
}
