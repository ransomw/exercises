#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "my_lua_utils.h"
#include "pathnames.h"

/***** 27 -- techniques for writing C functions **/

static void demo_l_map () {
  lua_State *L = lua_open();
  // remember, this style of function declaration is
  // not recommended in contrast with the library pattern.
  // if used, (as here for demo) it need go immediately
  // after lua_open()
  lua_pushcfunction(L, l_map);
  lua_setglobal(L, "map");
  load_lua_file_to_state(PATHNAME_MAP_DEMO, L);
  lua_close(L);
}

static void demo_l_split () {
  lua_State *L = lua_open();

  lua_pushcfunction(L, l_split);
  lua_setglobal(L, "split");
  load_lua_file_to_state(PATHNAME_SPLIT_DEMO, L);

  lua_close(L);
}

int main(void) {
  demo_l_map();
  demo_l_split();
}
