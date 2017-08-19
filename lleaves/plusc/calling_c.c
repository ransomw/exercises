#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "my_lua_utils.h"
#include "pathnames.h"

/***** 26 -- Calling C from Lua **/

/**
 * 26.1 -- C functions
 */

/**
 * simple example of a function to be called from Lua
 *
 * any function registered with lua must have this prototype
 * int (lua_State *L)
 */
static int l_dist_sq(lua_State *L) {
  /*
   * recall behavior of lua_to* functions from stack_demo.c
   * when indexed stack element doesn't have correct type
   */
  double x = lua_tonumber(L, 1);
  /*
   * ... so there's a utility function that throws an error
   *     if given an invalid argument
   */
  double y = luaL_checknumber(L, 2);
  double d_sq = x * x + y * y;
  lua_pushnumber(L, d_sq);
  /*
   * return the number of results (pushed to the lua stack)
   */
  return 1;
}

/**
 * the lowercase `l` indicates that this function need be called
 * immediately after `lua_open`
 */
static void add_fn_l_dist_sq(lua_State *l) {
  lua_pushcfunction(l, l_dist_sq);
  lua_setglobal(l, "dist_sq");
}

/**
 * 26.2 C libraries
 */

/*
 * although this library loading occurs within the lua interpeter
 * embedded into the calling_c binary, for a more typical use case,
 * after compiling the calling_c.so target, try running
 * calling_c_dyanmic.lua in the lua interpreter
 */

static const struct luaL_reg mylib[] = {
  {"dist_sq", l_dist_sq},
  {NULL, NULL} // '\0'-like
};

/**
 * this is the usual pattern for C libraries used by the interpreter:
 * define a function with this prototype to be passed to Lua's
 * `loadlib` function.
 */
int add_my_lib (lua_State *L) {
  /*
   * final parameter has to do with "upvalues"
   * todo: recall what upvalues are.
   */
  luaL_openlib(L, "mylib", mylib, 0);
  return 1;
}


int main(void) {
  lua_State *L = lua_open();
  add_fn_l_dist_sq(L);
  add_my_lib(L);

  load_lua_file_to_state(PATHNAME_CALLING_C, L);
}
