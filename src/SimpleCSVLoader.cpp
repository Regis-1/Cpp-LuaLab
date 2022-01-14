#include "SimpleCSVLoader.hpp"

SimpleCSVLoader::SimpleCSVLoader(const char* path, const char delimiter) : mDelimiter(delimiter) {
	mFS.open(path, std::ios::in);
	if (!mFS) {
		printf("Invalid file!\n");
		mError = true;
	}
}

SimpleCSVLoader::~SimpleCSVLoader() {
	mFS.close();
}

PlotData SimpleCSVLoader::GetAll() {
	std::string line;
	if(mFS)
		while (std::getline(mFS, line)) {
			AddRecord(line);
		}

	return mData;
}

//PRIVATE METHODS
void SimpleCSVLoader::AddRecord(std::string line) {
	size_t delimPos = line.find(mDelimiter);
	size_t lineEndPos = line.find('\n');

	std::string token1 = line.substr(0, delimPos);
	std::string token2 = line.substr(delimPos + 1, lineEndPos);
	double d1 = std::stod(token1);
	double d2 = std::stod(token2);

	mData.xs.push_back(d1);
	mData.ys.push_back(d2);
}