#include "LuaEmbedder.hpp"

LuaEmbedder::LuaEmbedder() {
	L = luaL_newstate();
}

LuaEmbedder::~LuaEmbedder() {
	lua_close(L);
}

void LuaEmbedder::test() {
	std::string cmd = "a = 7 + 11";

	int r = luaL_dostring(L, cmd.c_str());
	if (r == LUA_OK) {
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1)) {
			float a_in_cpp = (float)lua_tonumber(L, -1);
			printf("%f", a_in_cpp);
		}
	}
	else
		printf("LUA_OK is invalid!!");

}