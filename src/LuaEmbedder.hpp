#ifndef LUAEMBEDDER_HPP
#define LUAEMBEDDER_HPP

#include "SimpleCSVLoader.hpp"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#ifndef _WIN32
#pragma comment(lib, "src/vendor/lua542/liblua54.a")
#endif

extern PlotData luaData;

class LuaEmbedder {
private:
	lua_State* L = nullptr;

	void GetSizeOfArrays();

public:
	LuaEmbedder();
	~LuaEmbedder();

	void InterpreteLuaScript(const std::string path);
};

#endif LUAEMBEDDER_HPP