/* 
 * http://www.lua.org/pil/24.1.html 
 */

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>

int main(void) {
	char buff[256];
	int error;
	lua_State *L = luaL_newstate();
	luaL_requiref(L, "_G", luaopen_base, 1);
	luaL_requiref(L, "io", luaopen_io, 1);
	luaL_requiref(L, "package", luaopen_package, 1);
	//luaL_openlibs(L);

	while (fgets(buff, sizeof(buff), stdin) != NULL) {
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") || 
				lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}

	lua_close(L);
	return 0;
}
