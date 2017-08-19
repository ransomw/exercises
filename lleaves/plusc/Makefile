# todo: implicit rules
# (cf. info make sec. 10.3 Variables Used by Implicit Rules)

SHAREDIR = .

LIBLUA = -llua50 -llualib50
LIBLUA_INCDIR = /usr/include/lua50
LIBLUA_LIBDIR = /usr/lib

CFLAGS = -Wall -Wextra -DCONFIG_SHAREDIR='"$(SHAREDIR)"'
LIBS = $(LIBLUA) -L$(LIBLUA_LIBDIR) -I$(LIBLUA_INCDIR)

OBJ = my_lua_utils.o
BIN = first stack_demo extending calling_c techniques
SOBJ = calling_c.so

all: $(BIN)

first: first.c
	$(CC) -o first first.c $(LIBS)

stack_demo: stack_demo.c $(OBJ)
	$(CC) -o stack_demo stack_demo.c $(OBJ) $(LIBS)

extending: extending.c pathnames.h $(OBJ)
	$(CC) $(CFLAGS) -o extending extending.c $(OBJ) $(LIBS)

calling_c: calling_c.c pathnames.h $(OBJ)
	$(CC) $(CFLAGS) -o calling_c calling_c.c $(OBJ) $(LIBS)

techniques: techniques.c pathnames.h $(OBJ)
	$(CC) $(CFLAGS) -o techniques techniques.c $(OBJ) $(LIBS)

calling_c.so: calling_c.c pathnames.h $(OBJ)
	$(CC) $(CFLAGS) -shared -o calling_c.so calling_c.c $(OBJ) $(LIBS)

my_lua_utils.o: my_lua_utils.h my_lua_utils.c
	$(CC) -c my_lua_utils.c $(LIBS)

clean:
	rm -f $(OBJ) $(BIN) $(SOBJ)
