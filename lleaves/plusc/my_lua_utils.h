#ifndef MY_LUA_UTILS_H
#define MY_LUA_UTILS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


void dump_stack (lua_State *L);
char *get_lua_type_str (lua_State *L, int idx_stack);

int load_lua_file_to_state (char *filename, lua_State *L);
lua_State *load_lua_file (char *filename);

void call_lua_va (lua_State *L,
                  const char *func, const char *sig,
                  ...);

int l_map(lua_State *L);
int l_split(lua_State *L);

#endif				/* MY_LUA_UTILS_H */
