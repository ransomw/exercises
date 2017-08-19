#include <stdio.h>
#include <string.h>

 // functions have lua_* prefix
#include <lua.h>
// functions have luaL_* prefix
#include <lauxlib.h>
#include <lualib.h>

/**
 * invoke the lua interpreter.  use ^D to quit to avoid memory leaks.
 */
int main (void) {
  char buff[256];
  int err;
  lua_State *L = lua_open(); // lua.h

  luaopen_base(L); // lualib.h
  luaopen_table(L);
  luaopen_io(L);
  luaopen_string(L);
  luaopen_math(L);
  // this would replace the above for 5.1+
  /* luaL_openlibs(L); */

  // NULL is EOF
  while (fgets(buff, sizeof(buff), stdin) != NULL) {
    // compile and push onto call stack
    if (! (err = luaL_loadbuffer(L,
                                 buff,
                                 strlen(buff),
                                 "line"
                                 ))) {
      err = lua_pcall(L, 0, 0, 0);
    }
    if (err) {
      fprintf(stderr, "%s%c", lua_tostring(L, -1), '\n');
      // pop error message from stack
      lua_pop(L, 1);
    }
  }

  lua_close(L);
  return 0;
}
