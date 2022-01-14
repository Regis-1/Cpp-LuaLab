#pragma once
#include <string>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#ifndef _WIN32
#pragma comment(lib, "src/vendor/lua542/liblua54.a")
#endif

class LuaEmbedder {
private:
	lua_State* L = nullptr;

public:
	LuaEmbedder();
	~LuaEmbedder();

	void test();
};