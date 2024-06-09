#include "Mod.hpp"

Mod::Mod()
{
    uniqueName = "";
    name = "";
    polarity = "";
    rarity = "";
    codexSecret = false;
    baseDrain = 0;
    fusionLimit = 0;
    excludeFromCodex = false;
    isUtility = false;
    compatName = "";
    type = "";
    description = {};
    subtype = "";
    levelStats = {};
    modSet = "";
}

Mod::Mod(nlohmann::json Json)
{
    try
    {
        uniqueName = Json["uniqueName"];
        name = Json["name"];
        polarity = Json["polarity"];
        rarity = Json["rarity"];
        codexSecret = Json["codexSecret"];
        baseDrain = Json["baseDrain"];
        fusionLimit = Json["fusionLimit"];
        if (Json.contains("excludeFromCodex")) { excludeFromCodex = Json["excludeFromCodex"]; } else { excludeFromCodex = false; }
        if (Json.contains("isUtility")) { isUtility = Json["isUtility"]; } else { isUtility = false; }
        compatName = Json["compatName"];
        type = Json["type"];
        if (Json.contains("subtype")) { subtype = Json["subtype"]; } else { subtype = ""; }
        description = {};
        for (int i = 0; i < Json["description"].size(); i++)
        {
            description.push_back(Json["description"][i]);
        }
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
        if (Json.contains("modSet")) { modSet = Json["modSet"]; } else { modSet = ""; }
    }
    catch (...)
    {
        uniqueName = "";
        name = "";
        polarity = "";
        rarity = "";
        codexSecret = false;
        baseDrain = 0;
        fusionLimit = 0;
        excludeFromCodex = false;
        isUtility = false;
        compatName = "";
        type = "";
        description = {};
        subtype = "";
        levelStats = {};
        modSet = "";
        std::cout << "Error initializing Mod object, default object initialized instead." << std::endl;
    }
}


RivenMod::RivenMod()
{
    uniqueName = "";
    name = "";
    polarity = "";
    rarity = "";
    codexSecret = false;
    baseDrain = 0;
    fusionLimit = 0;
    excludeFromCodex = false;
    upgradeEntries = "";
    availableChallenges = "";
    levelStats = {};
}
RivenMod::RivenMod(nlohmann::json Json)
{
    try
    {
        uniqueName = Json["uniqueName"];
        name = Json["name"];
        polarity = Json["polarity"];
        rarity = Json["rarity"];
        codexSecret = Json["codexSecret"];
        baseDrain = Json["baseDrain"];
        fusionLimit = Json["fusionLimit"];
        excludeFromCodex = Json["excludeFromCodex"];
        if (Json.contains("upgradeEntries")) { upgradeEntries = Json["upgradeEntries"]; } else { upgradeEntries = ""; }
        if (Json.contains("availableChallenges")) { availableChallenges = Json["availableChallenges"]; } else { availableChallenges = ""; }
        levelStats = {};
        for (auto& a : Json["levelStats"])
        {
            levelStats.push_back(a);
        }
    }
    catch (...)
    {
        uniqueName = "";
        name = "";
        polarity = "";
        rarity = "";
        codexSecret = false;
        baseDrain = 0;
        fusionLimit = 0;
        excludeFromCodex = false;
        upgradeEntries = "";
        availableChallenges = "";
        levelStats = {};
    }
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
    std::cout << "excludeFromCodex: " << excludeFromCodex << std::endl;
    std::cout << "isUtility: " << isUtility << std::endl;
    std::cout << "compatName: " << compatName << std::endl;
    std::cout << "type: " << type << std::endl;
    std::cout << "description: " << std::endl;
    for (int i = 0; i < description.size(); i++)
    {
        std::cout << "   n°" << i << std::endl;
        std::cout << "   " << description[i] << std::endl;
    }
    std::cout << "subtype: " << subtype << std::endl;
    std::cout << "levelStats: " << std::endl;
    for (auto& a : levelStats)
    {
        std::cout << "   n°" << std::endl;
        for (auto& b : a)
        {
            std::cout << "      -" << b << std::endl;
        }
    }
    std::cout << "modSet: " << modSet << std::endl;
}