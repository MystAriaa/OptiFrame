#include <string>
#include <vector>
#include <json.hpp>
#include <iostream>
#include "usefullFunction.hpp"

class Arcane {
public:
	std::string name;
	std::string uniqueName;
	bool codexSecret;
	std::string rarity;
	bool excludeFromCodex;
	std::vector<std::vector<std::string>> levelStats;

	Arcane();
	Arcane(nlohmann::json Json);
	~Arcane() {};

	void debugDisplayData();
};