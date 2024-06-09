#include "Mod.hpp"

void Mod::loadData(
    std::string t_uniqueName,
    std::string t_name,
    std::string t_polarity,
    std::string t_rarity,
    bool t_codexSecret,
    int t_baseDrain,
    int t_fusionLimit,
    std::string t_compatName,
    std::string t_type,
    std::vector<std::string> t_description)
{
    uniqueName = t_uniqueName;
    name = t_name;
    polarity = t_polarity;
    rarity = t_rarity;
    codexSecret = t_codexSecret;
    baseDrain = t_baseDrain;
    fusionLimit = t_fusionLimit;
    compatName = t_compatName;
    type = t_type;
    description = t_description;
}

AuraMod::AuraMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"], Json["description"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

WarframeMod::WarframeMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"], Json["description"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

StanceMod::StanceMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"], Json["description"]);
}

MeleeMod::MeleeMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"], Json["description"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

PrimaryMod::PrimaryMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"], Json["description"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

SecondaryMod::SecondaryMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"], Json["description"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}








//--------------------------------------
// Debug methodes

void Mod::debugDisplayData()
{
    std::cout << std::endl;
    std::cout << "[Debug Display Data]" << std::endl;
    std::cout << "uniqueName: " << uniqueName << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "polarity: " << polarity << std::endl;
    std::cout << "rarity: " << rarity << std::endl;
    std::cout << "codexSecret: " << codexSecret << std::endl;
    std::cout << "baseDrain: " << baseDrain << std::endl;
    std::cout << "fusionLimit: " << fusionLimit << std::endl;
    std::cout << "compatName: " << compatName << std::endl;
    std::cout << "type: " << type << std::endl;

    std::cout << "description: " << std::endl;
    for (int i = 0; i < description.size(); i++)
    {
        std::cout << "   n°" << i << std::endl;
        std::cout << "   " << description[i] << std::endl;
    }
}

void AuraMod::debugDisplayData()
{
    Mod::debugDisplayData();
    std::cout << "levelStats: " << std::endl;
    for (int i = 0; i < levelStats.size(); i++)
    {
        std::cout << "   " << levelStats[i] << std::endl;
    }
    std::cout << std::endl;
}

void WarframeMod::debugDisplayData()
{
    Mod::debugDisplayData();
    std::cout << "levelStats: " << std::endl;
    for (int i = 0; i < levelStats.size(); i++)
    {
        std::cout << "   " << levelStats[i] << std::endl;
    }
    std::cout << std::endl;
}

void StanceMod::debugDisplayData()
{
    Mod::debugDisplayData();
}

void MeleeMod::debugDisplayData()
{
    Mod::debugDisplayData();
    std::cout << "levelStats: " << std::endl;
    for (int i = 0; i < levelStats.size(); i++)
    {
        std::cout << "   " << levelStats[i] << std::endl;
    }
    std::cout << std::endl;
}

void PrimaryMod::debugDisplayData()
{
    Mod::debugDisplayData();
    std::cout << "levelStats: " << std::endl;
    for (int i = 0; i < levelStats.size(); i++)
    {
        std::cout << "   " << levelStats[i] << std::endl;
    }
    std::cout << std::endl;
}

void SecondaryMod::debugDisplayData()
{
    Mod::debugDisplayData();
    std::cout << "levelStats: " << std::endl;
    for (int i = 0; i < levelStats.size(); i++)
    {
        std::cout << "   " << levelStats[i] << std::endl;
    }
    std::cout << std::endl;
}