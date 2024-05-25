#include "Mod.h"
#include "iostream"

void Mod::loadData(
    std::string t_uniqueName,
    std::string t_name,
    std::string t_polarity,
    std::string t_rarity,
    bool t_codexSecret,
    int t_baseDrain,
    int t_fusionLimit,
    std::string t_compatName,
    std::string t_type)
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
}

AuraMod::AuraMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

WarframeMod::WarframeMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

StanceMod::StanceMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"]);
    description = Json["description"][0];
}

MeleeMod::MeleeMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

PrimaryMod::PrimaryMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;
}

SecondaryMod::SecondaryMod(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["polarity"], Json["rarity"], Json["codexSecret"], Json["baseDrain"], Json["fusionLimit"], Json["compatName"], Json["type"]);
    std::vector<std::string> tempVector = {};
    for (int i = 0; i < Json["levelStats"].size(); i++)
    {
        tempVector.push_back(Json["levelStats"][i]["stats"][0]);
    }
    levelStats = tempVector;