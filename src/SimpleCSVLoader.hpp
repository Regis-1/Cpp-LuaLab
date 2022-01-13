#pragma once
#include <vector>
#include <fstream>
#include <string>

struct PlotData {
	std::vector<double> xs;
	std::vector<double> ys;
};

class SimpleCSVLoader {
private:
	std::ifstream mFS;
	PlotData mData;
	char mDelimiter;

	void AddRecord(std::string line);
public:
	SimpleCSVLoader() = delete;
	SimpleCSVLoader(const char* path, const char delimiter = ';');
	~SimpleCSVLoader();
	
	PlotData GetAll();
};