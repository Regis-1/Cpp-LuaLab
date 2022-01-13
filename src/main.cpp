#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <windows.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const char WINDOW_TITLE[7] = "LuaLab";
const int WIN_WIDTH = 640;
const int WIN_HEIGHT = 480;

int main(int argc, char* argv[]) {
	//Initializing...
	sf::RenderWindow mainWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WINDOW_TITLE);
	mainWindow.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(mainWindow);

	sf::Clock deltaClock;
	//Main body
	while (mainWindow.isOpen()) {
		sf::Event event;
		while (mainWindow.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				mainWindow.close();
			}
		}

		ImGui::SFML::Update(mainWindow, deltaClock.restart());

		//Beggining of ImGui window
		ImGui::Begin("Data", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize);
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Data Source")) {
				if (ImGui::MenuItem("CSV file..")) {
					//GET CSV FILE
				}
				if (ImGui::MenuItem("Lua script..")) {
					//GET LUA SCRIPT
				}
				if (ImGui::MenuItem("TEST", "Ctrl-L")) {
					//OPEN CUSTOM CONSOLE
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		//Ending of ImGui window
		ImGui::End();

		//Renderig...
		mainWindow.clear(sf::Color(0));
		ImGui::SFML::Render(mainWindow);
		mainWindow.display();
	}

	//Ending...
	ImGui::SFML::Shutdown();
	mainWindow.close();
	return 0;
}