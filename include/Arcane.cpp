#include "Arcane.hpp"

Arcane::Arcane() {
	name = "";
	uniqueName = "";
	codexSecret = false;
	rarity = "";
	excludeFromCodex = false;
	levelStats = {};
}
Arcane::Arcane(nlohmann::json Json)
{
	try
	{
		name = Json["name"];
		uniqueName = Json["uniqueName"];
		codexSecret = Json["codexSecret"];
		rarity = Json["rarity"];
		if (Json.contains("excludeFromCodex")) { excludeFromCodex = Json["excludeFromCodex"]; } else { excludeFromCodex = false; }
		levelStats = {};
		for (int i = 0; i < Json["levelStats"].size(); i++)
		{
			std::vector<std::string> tempVector = {};
			for (auto& obj : Json["levelStats"][i]["stats"])
			{
				tempVector.push_back(obj);
			}
			levelStats.push_back(tempVector);
		}
	}
	catch (...)
	{
		name = "";
		uniqueName = "";
		codexSecret = false;
		rarity = "";
		excludeFromCodex = false;
		levelStats = {};
		std::cout << "Error initializing Arcane object, default object initialized instead." << std::endl;
	}
}





//--------------------------------------
// Debug methodes

void Arcane::debugDisplayData()
{
	std::cout << std::endl;
	std::cout << "[Debug Display Data]" << std::endl;
	std::cout << "uniqueName: " << uniqueName << std::endl;
	std::cout << "name: " << name << std::endl;
	std::cout << "rarity: " << rarity << std::endl;
	std::cout << "codexSecret: " << codexSecret << std::endl;
	std::cout << "excludeFromCodex: " << excludeFromCodex << std::endl;
	std::cout << "levelStats: " << std::endl;
	for (auto& a : levelStats)
	{
		std::cout << "   n°" << std::endl;
		for (auto& b : a)
		{
			std::cout << "      -" << cleanRetourChariot(b) << std::endl;
		}
	}
}