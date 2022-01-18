#ifndef APPMANAGER_HPP
#define APPMANAGER_HPP

#include "imgui.h"
#include "imgui-SFML.h"
#include "LuaEmbedder.hpp"
#include "pbPlots.hpp"
#include "supportLib.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum DataSource {
	NONE,
	CSV,
	SCRIPT,
	CONSOLE
};

class AppManager {
private:
	int mScrWidth;
	int mScrHeight;
	const char* mTitle = nullptr;

	//SFML objects
	sf::RenderWindow mAppWindow;
	sf::Clock mDeltaClock;
	sf::Texture mTexture;
	sf::Sprite mSprite;
	bool mPlotExists = false;

	//ImGui
	DataSource mDS = DataSource::NONE;
	char mFilePathBuffer[255] = "";
	bool mShowAuxWindow = true;

	void EventHandling();
	void RenderDataWindow();
	void ShowFilePathWindow(const char* label);
	void PlotDataGraph(PlotData& data);
	void LoadSprite();
	void RunScript(const std::string path);
public:
	AppManager() = delete;
	AppManager(const AppManager& other) = delete;
	AppManager(const int width, const int height, const char* title);
	~AppManager();

	void Run();
};

#endif