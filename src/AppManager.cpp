#include "AppManager.hpp"
PlotData luaData = {};

AppManager::AppManager(const int width, const int height, const char* title)
	:mScrWidth(width), mScrHeight(height), mTitle(title) {

	mAppWindow.create(sf::VideoMode(width, height), title);
	mAppWindow.setVerticalSyncEnabled(true);

	mSprite.setPosition(sf::Vector2f(0.0f, 0.0f));

	ImGui::SFML::Init(mAppWindow);

	mAppWindow.clear(sf::Color(0));
}

AppManager::~AppManager() {
	ImGui::SFML::Shutdown();
	mAppWindow.close();
}

void AppManager::Run() {
	while (mAppWindow.isOpen()) {
		EventHandling();

		ImGui::SFML::Update(mAppWindow, mDeltaClock.restart());
		
		RenderDataWindow();
		if(mShowAuxWindow)
			switch (mDS)
			{
			case CSV:
				ShowFilePathWindow("CSV file path");
				break;
			case SCRIPT:
				ShowFilePathWindow("Lua script path");
				break;
			default:
				break;
			}

		mAppWindow.clear();
		if (mPlotExists)
			mAppWindow.draw(mSprite);
		ImGui::SFML::Render(mAppWindow);
		mAppWindow.display();
	}
}

//PRIVATE METHODS
void AppManager::EventHandling() {
	sf::Event event;
	while (mAppWindow.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed) {
			mAppWindow.close();
		}
	}
}

void AppManager::RenderDataWindow() {
	ImGui::SetNextWindowSize(ImVec2(100, 30));
	ImGui::Begin("Data", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Data Source")) {
			if (ImGui::MenuItem("CSV file.."))
				mDS = DataSource::CSV;
			if (ImGui::MenuItem("Lua script.."))
				mDS = DataSource::SCRIPT;
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::End();

	if (mDS != DataSource::NONE)
		mShowAuxWindow = true;
}

void AppManager::ShowFilePathWindow(const char* label) {
	ImGui::SetNextWindowSize(ImVec2(350, 80));
	if (!ImGui::Begin(label, &mShowAuxWindow, ImGuiWindowFlags_NoResize)) {
		ImGui::End();
	}
	else {
		ImGui::InputText(label, mFilePathBuffer, 255);
		if (ImGui::Button("Load")) {
			//LOAD DATA
			if (mDS == DataSource::CSV) {
				//load csv
				SimpleCSVLoader csvLoader(mFilePathBuffer);
				if (!csvLoader.mError) {
					PlotData data = csvLoader.GetAll();
					PlotDataGraph(data);
					LoadSprite();
				}
			}
			else if (mDS == DataSource::SCRIPT) {
				RunScript(mFilePathBuffer);
				PlotDataGraph(luaData);
				LoadSprite();
			}
		}
		ImGui::End();
	}
	if (!mShowAuxWindow)
		mDS = DataSource::NONE;
}

void AppManager::PlotDataGraph(PlotData& data) {
	StringReference* errorMessage = new StringReference();
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	bool success = DrawScatterPlot(imageReference, mScrWidth, mScrHeight, &(data.xs), &(data.ys), errorMessage);

	if (success) {
		std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, "lastPlot.png");
		DeleteImage(imageReference->image);
		delete pngdata;
	}
	else {
		std::cerr << "Error: ";
		for (wchar_t c : *errorMessage->string) {
			std::wcerr << c;
		}
		std::cerr << std::endl;
	}

	delete errorMessage;
	delete imageReference;
}

void AppManager::LoadSprite() {
	if (!mTexture.loadFromFile("lastPlot.png")) {
		printf("Error while rendering plot texture!\n");
		return;
	}
	mSprite.setTexture(mTexture);
	mPlotExists = true;
}

void AppManager::RunScript(const std::string path) {
	LuaEmbedder lua;
	lua.InterpreteLuaScript(path);
}