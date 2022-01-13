#include "AppManager.hpp"

const char WIN_TITLE[7] = "LuaLab";
const int WIN_WIDTH = 640;
const int WIN_HEIGHT = 480;

int main(int argc, char* argv[]) {
	AppManager manager(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	manager.Run();

	return 0;
}