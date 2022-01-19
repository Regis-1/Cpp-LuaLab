#include "LuaEmbedder.hpp"

//HOST FUNCTIONS

std::vector<double> GetDoubleVector(lua_State * L) {
	std::vector<double> v;
	double tmp = 0;
	lua_pushnil(L);
	while (lua_next(L, -2)) {
		tmp = (double)lua_tonumber(L, -1);
		//printf("%f - cpp", tmp);
		v.push_back(tmp);
		lua_pop(L, 1);
	}
	//printf("\n");
	return v;
}

int Plot(lua_State* L)
{
	if (lua_isnil(L, -1) or lua_isnil(L, -2)) {
		printf("One of the argument is nil!\n");
		return 1;
	}

	size_t yLen = lua_rawlen(L, -1);
	size_t xLen = lua_rawlen(L, -2);

	if (xLen != yLen) {
		printf("Data arrays' size mismatch!\nXs => %d\tYs => %d", (int)xLen, (int)yLen);
		return 1;
	}

	std::vector<double> luaY = GetDoubleVector(L);
	lua_pop(L, -2);
	std::vector<double> luaX = GetDoubleVector(L);

	luaData = { luaX, luaY };

	lua_pop(L, lua_gettop(L));
	return 0;
}

//PUBLIC METHODS

LuaEmbedder::LuaEmbedder() {
	L = luaL_newstate();
	luaL_openlibs(L);

	lua_register(L, "H_Plot", Plot);
}

LuaEmbedder::~LuaEmbedder() {
	lua_close(L);
}

void LuaEmbedder::InterpreteLuaScript(const std::string path) {
	luaL_dofile(L, path.c_str());
}

//PRIVATE METHODS

void LuaEmbedder::GetSizeOfArrays() {

}