#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "my_lua_utils.h"

/**
 * the stack printing facility from chap 24
 */
void dump_stack (lua_State *L) {
  int idx_curr;
  int idx_top = lua_gettop(L);
  for (idx_curr = 1; idx_curr <= idx_top; idx_curr++) {
    int curr_type = lua_type(L, idx_curr);
    switch (curr_type) {
    case LUA_TBOOLEAN:
      printf(lua_toboolean(L, idx_curr) ? "true" : "false");
      break;
    case LUA_TNUMBER:
      printf("%g", lua_tonumber(L, idx_curr));
      break;
    case LUA_TSTRING:
      printf("\"%s\"", lua_tostring(L, idx_curr));
      break;
    default:
      printf("%s", lua_typename(L, curr_type));
      break;
    }
    printf(" "); // seperator for readability
  }
  printf("\n"); // end of listing
}

/**
 * a type printing facility using the (complete)
 * list of types in chap 24
 */
char *get_lua_type_str (lua_State *L, int idx_stack) {
  switch (lua_type(L, idx_stack)) {
  case LUA_TNIL:
    return "nil";
  case LUA_TBOOLEAN:
    return "boolean";
  case LUA_TNUMBER:
    return "number";
  case LUA_TSTRING:
    return "string";
  case LUA_TTABLE:
    return "table";
  case LUA_TFUNCTION:
    return "function";
  case LUA_TUSERDATA:
    return "userdata";
  case LUA_TTHREAD:
    return "thread";
  default:
    return "unknown";
  }
}

/***** 25 -- extending your application **/

/**
 * the pattern throughout most of these examples will be _not_
 * to use the same lua_State throughout the C application,
 * instead sandboxing each use of the lua environment in
 * a new lua_State opened by this function and initialized
 * with [in particular, the globals] defined in `filename`.
 *
 * so it's important to remember to `lua_close` the return value
 * of this function after the state loaded from the file is used.
 */
int load_lua_file_to_state (char *filename,
                            lua_State *L) {
  luaopen_base(L); // lualib.h
  luaopen_io(L);
  luaopen_string(L);
  luaopen_math(L);

  // pushes file onto stack
  if (luaL_loadfile(L, filename)) {
    fprintf(stderr, "couldn't load config_00 file '%s'", filename);
    return 1;
  }
  // ... such that it's a function with zero args, zero r.v.s
  if (lua_pcall(L, 0, 0, 0)) {
    fprintf(stderr, "couldn't run config_00 file '%s':\n%s\n",
            filename, lua_tostring(L, -1));
    return 1;
  }

  return 0;
}

lua_State *load_lua_file (char *filename) {
  // this lua_State is opened expressly for loading the file
  lua_State *L = lua_open();
  if (load_lua_file_to_state(filename, L)) {
    lua_close(L);
    return NULL;
  }
  return L;
}

/**
 * the generic lua function call from 25.3
 * `func` -- name of the function to be called
 * `sig` -- type signature of the function,
 *   a single character for each parameter and return value
 *   (see switches below) with a '>' delimiting params and rvs.
 *   the '>' may be omitted in the case no rvs.
 */
void call_lua_va (lua_State *L,
                  // recall that const pointers indicate that
                  // the function doesn't change the referenced
                  // values and that the results of doing otherwise
                  // are impl-defined
                  const char *func, const char *sig,
                  // C variable-length arg list syntax (K&R 7.3)
                  ...) {
  // va_list type defined in stdarg.h
  // it is an argument pointer incremented when va_arg
  // gets each successive variable argument.
  va_list ap;
  int num_arg; // number of args to lua function
  int num_res; // number of results from the lua function
  // remaining signature: used to keep original pointer accessible
  const char *sig_rem = sig;
  // keep num_res constant
  int idx_curr_res;
  // va_start() always takes the final named argument
  // as its second parameter in order to set va_list ptr
  va_start(ap, sig);
  lua_getglobal(L, func);

  /* push args onto the lua stack */
  num_arg = 0;
  while (*sig_rem) {
    // leaving this half-understood deref&increment idiom in place
    // .. and viewing it idiomatically as "deref then increment"
    switch (*sig_rem++) {
    case 'd': // double
      lua_pushnumber(L, va_arg(ap, double));
      break;
    case 'i': // int
      lua_pushnumber(L, va_arg(ap, int));
      break;
    case 's': // string
      lua_pushstring(L, va_arg(ap, char *));
      break;
    case '>':
      goto endwhile;
    default:
      fprintf(stderr, "invalid parameter type (%c) "
              "in function signature '%s'",
              *(sig_rem - 1), sig);
      return;
    }
    num_arg += 1;
    if (!lua_checkstack(L, 1)) {
      fprintf(stderr, "not enough room on the stack for all "
              "of `%s`'s parameters", func);
    }
  } endwhile: // label for goto

  /* call the lua function */
  num_res = strlen(sig_rem);
  if (lua_pcall(L, num_arg, num_res, 0) != 0) {
    fprintf(stderr, "error running lua function `%s`: %s\n",
            func, lua_tostring(L, -1));
    return;
  }

  /* get results (in the back... of a mag-a-zine...) */
  idx_curr_res =  -1 * num_res; // lua stack index
  while (*sig_rem) {
    switch (*sig_rem++) {
    case 'd': // double
      if (!lua_isnumber(L, idx_curr_res)) {
        fprintf(stderr,
                "expected %dth return value type to convert to "
                "'number',  got '%s'.\n",
                idx_curr_res, get_lua_type_str(L, idx_curr_res));
        return;
      }
      *va_arg(ap, double *) = lua_tonumber(L, idx_curr_res);
      break;
    case 'i': // int
      if (!lua_isnumber(L, idx_curr_res)) {
        fprintf(stderr,
                "expected %dth return value type to convert to "
                "'number',  got '%s'.\n",
                idx_curr_res, get_lua_type_str(L, idx_curr_res));
        return;
      }
      *va_arg(ap, int *) = (int) lua_tonumber(L, idx_curr_res);
      break;
    case 's': // string
      if (!lua_isstring(L, idx_curr_res)) {
        fprintf(stderr,
                "expected %dth return value type to convert to "
                "'string',  got '%s'.\n",
                idx_curr_res, get_lua_type_str(L, idx_curr_res));
        return;
      }
      // recall strings are char pointers, so string pointers
      // are pointers to char pointers.
      *va_arg(ap, char **) = lua_tostring(L, idx_curr_res);
      // todo: recall lua_tostring returns a pointer to the
      //       string used by the interpreter.
      //       so as a safety measure, edit this to copy the string
      //       and return a pointer to that.
      //    ...hopefully this'll get rid of the gcc warning
      //"assignment discards ‘const’ qualifier from pointer target type"
      //  experiment with how this idea plays with popping results
      //  from the lua stack before this function returns.
      break;
    default:
      fprintf(stderr, "invalid return value type (%c) "
              "in function signature '%s'",
              *(sig_rem - 1), sig);
      return;
    }
    idx_curr_res += 1;
  }

  va_end(ap); // "whatever" --- K&R :-)
}

/***** 27 -- techniques for writing C functions **/

/**
 * this C impl of the usual functional programming `map`
 * function demonstrates the `lua_rawgeti` and `lua_rawseti`
 * functions for array manipulation.
 *
 * the table (array) to map over is expected to be at the
 * bottom of the stack, and the function is expected to
 * be the next value on the stack.
 * recall that each function call gets its own stack frame,
 * so practically, this means that a lua function call might
 * look like `map(arr, func)`
 *
 * return values are put in place of original values in the array
 * at the bottom of the stack
 *
 * !!! some new functions are introduced here, so check
 *     inline comments
 */
// this l_* convention is pretty good and probably ought to
// be applied uniformly
int l_map(lua_State *L) {
  // usual points for and against preprocessor apply..
  // .. for now, at least keep the code clear
  const int sidx_table = 1; // 's' for "stack"
  const int sidx_func = 2;
  int idx_key;
  int len_arr;

  /*
   * raises an error (in C? lua?) ... sandbox demo
   * if stack index doesn't have appropriate type
   */
  luaL_checktype(L, sidx_table, LUA_TTABLE);
  luaL_checktype(L, sidx_func, LUA_TFUNCTION);
  /*
   * just like `array.getn(my_arr)` in lua,
   * 'cept there's always the stack index to fuss about in C
   */
  len_arr = luaL_getn(L, sidx_table);

  // remember, unlike C, indexes from 1
  for (idx_key=1; idx_key <= len_arr; idx_key++) {
    // func to top of stack
    lua_pushvalue(L, sidx_func);
    // next value to on top of that
    lua_rawgeti(L, sidx_table, idx_key);
    /*
     * like lua_pcall -- one param, one rv -- except
     * it returns an error code to C
     * rather than throwing an error in lua
     */
    lua_call(L, 1, 1);
    lua_rawseti(L, sidx_table, idx_key);
  }
  return 0; // all's well
}

/**
 * split string on single-character separator
 */
int l_split(lua_State *L) {
  /*
   * recall that
   * `const <type>*` is a mutable pointer to an immutable value
   * while
   * `<type>* const` is an immutable pointer to a mutable value
   * ... and `const <type>* const` keeps everything immutable
   */
  const char *str_rem = luaL_checkstring(L, 1);
  const char sep = *luaL_checkstring(L, 2);
  const char *curr_end; // end of current split
  int idx_table = 1;

  lua_newtable(L); // this'll be the result
  /*
   * char * strchr(const char *cs, (char) int c)
   *  returns a pointer to the first instance of c in cs
   *  or NULL if c is not present in cs
   */
  while((curr_end = strchr(str_rem, sep)) != NULL) {
    // recall that pointer subtraction returns an int (num items)
    lua_pushlstring(L, str_rem, curr_end - str_rem);
    lua_rawseti(L, -2, idx_table);
    idx_table += 1;
    str_rem = curr_end + 1;
  }

  lua_pushstring(L, str_rem);
  lua_rawseti(L, -2, idx_table);

  return 1; // the table is back at the top of the stack
}
