#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "my_lua_utils.h"
#include "pathnames.h"

#define MAX_COLOR 255

static struct ColorTable {
  char *name;
  unsigned char red, green, blue;
} colortables[] = {
  {"BLACK", MAX_COLOR, MAX_COLOR, MAX_COLOR},
  {"WHITE", 0, 0, 0},
  {"RED", MAX_COLOR, 0, 0},
  {"GREEN", 0, MAX_COLOR, 0},
  {"BLUE", 0, 0, MAX_COLOR},
  {NULL, 0, 0, 0} // '\0'-like
};

/***** 25 -- extending your application **/

/**
 * this is the uber-simple example from the beginning of the
 * chapter: it grabs the name of of specific variable (`times`)
 * out of the file and converts it to a C type.
 */
static void load_config_00 (char *filename, int *how_many) {
  lua_State *L = load_lua_file(filename);
  if (L == NULL) {
    return;
  }

  // `lua_getglobal` pushes the named variable onto the stack
  lua_getglobal(L, "times");
  // and from here it's mostly like stack_demo.c
  if (!lua_isnumber(L, -1)) {
    fprintf(stderr, "`times' ought be a number\n");
    return;
  }
  *how_many = (int) lua_tonumber(L, -1);

  lua_close(L);
}

/**
 * 25.1 -- tables
 */

// ----
// accessing a table defined in lua

/**
 * grab a color field from the lua environment to C,
 * provided a color table is on top of the stack.
 */
int getfield_color (lua_State *L, const char *key) {
  int res;
  lua_pushstring(L, key);
  /*
   * gets the index of a table, pops a key from the stack
   * and pushes the value of the table at that key on top
   * of the stack
   */
  lua_gettable(L, -2);
  if (!lua_isnumber(L, -1)) {
    fprintf(stderr, "table value `%s` is type '%s',"
            "expected 'number'.\n", key,
            get_lua_type_str(L, -1));
    return 0;
  }
  res = (int) (lua_tonumber(L, -1) * MAX_COLOR);
  // this function doesn't close the lua env,
  // so it is important to leave the stack in its original state
  lua_pop(L, 1);
  return res;
}

static void print_color (lua_State *L, char *color_name) {
  lua_getglobal(L, color_name);

  if (!lua_istable(L, -1)) {
    fprintf(stderr, "`%s` is type '%s',"
            "expected 'table' (of colors).\n",
            color_name,
            get_lua_type_str(L, -1));
    return;
  }

  printf("`%s`'s colors -- "
         "r: %d, g: %d, b: %d\n", color_name,
         getfield_color(L, "r"),
         getfield_color(L, "g"),
         getfield_color(L, "b"));
}

// ----
// writing to table accessible from lua

static void setfield_color (lua_State *L, const char *index, int color) {
  lua_pushstring(L, index);
  lua_pushnumber(L, ((double) color / MAX_COLOR));
  /*
   * lua_settable()
   * takes table stack position as arg, assumes key and val
   * are at indices -2 and -1, respectively.
   * it pops these top two values from the stack
   */
  lua_settable(L, -3);
}

static void setcolor (lua_State *L, struct ColorTable *ct) {
  /*
   * creates a new table and pushes it to top of stack
   */
  lua_newtable(L);
  // recall some_struct.field, some_struct_ptr->field syntaxes
  setfield_color(L, "r", ct->red);
  setfield_color(L, "g", ct->green);
  setfield_color(L, "b", ct->blue);
  /*
   * pops top and sets it to global variable
   * with the given name (string)
   */
  lua_setglobal(L, ct->name);
}

static void setcolors (lua_State *L) {
  int idx = 0;
  luaopen_base(L);
  luaopen_table(L);
  while (colortables[idx].name != NULL) {
    setcolor(L, &colortables[idx]);
    idx += 1;
  }
}

// ----
// all together now

static void colors_demo (char *filename) {
  lua_State *L = lua_open();
  setcolors(L);
  load_lua_file_to_state(filename, L);
  // set directly in lua file
  print_color(L, "the_kids");
  // set in lua file using table added to globals by `setcolors`
  print_color(L, "the_wall");
}

// ... there's another example in this section.  it has more
//   to do with program design (later chapters) than tables.

/**
 * 25.2 -- calling lua functions
 */
static double call_config_dist (char *filename,
                                double x, double y) {
  double res;
  lua_State *L = load_lua_file(filename);

  //// call the function //
  lua_getglobal(L, "dist");
  // parameters for function calls are those values
  // on top of the function in the stack
  lua_pushnumber(L, x);
  lua_pushnumber(L, y);
  // two parameters, one return value.
  if (lua_pcall(L, 2, 1, 0)) {
    fprintf(stderr, "error running lua config function `dist`:\n%s\n",
            lua_tostring(L, -1));
    return 0;
  }

  //// get the return value //
  if (!lua_isnumber(L, -1)) {
    fprintf(stderr, "function `dist` returned type '%s',"
            "expected 'number'.\n",
            get_lua_type_str(L, -1));
    return 0;
  }
  res = lua_tonumber(L, -1);
  lua_pop(L, 1); // for good measure, get rid of the rv

  lua_close(L);
  return res;
}

/**
 * 25.3 -- a generic call function (from my_lua_utils.c)
 */
static void generic_call_demo (char *filename) {
  lua_State *L = lua_open();
  double dist;
  load_lua_file_to_state(filename, L);
  // typecasts on literals are super-important for this
  // varargs impl since the type can't be inferred from
  // call_lua_va's function signature
  call_lua_va(L, "dist", "dd>d", (double) 6, (double) 8, &dist);
  printf("[generically]"
         "called config dist() to find dist(6, 8)=%.2f\n", dist);
  lua_close(L);
}

int main (void) {
  int times;


  load_config_00(PATHNAME_CONFIG, &times);

  printf("loaded config to find times=%d\n", times);
  printf("called config dist() to find dist(3, 4)=%.2f\n",
         call_config_dist(PATHNAME_CONFIG, 3, 4));

  colors_demo(PATHNAME_CONFIG);

  generic_call_demo(PATHNAME_CONFIG);
}
