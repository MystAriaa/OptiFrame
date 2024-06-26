#include "Mod.hpp"


EffectMod::EffectMod()
{
    effectJson["weapon"]["utility"] = { "accuracy", "maxAmmo", "ammoPickup", "noiseLevel", "magazineSize", "spread", "projectileSpeed", "comboChance", "comboDuration", "initalCombo", "comboEfficiency", "blockingAngle", "numberBounce" };
    effectJson["weapon"]["damage"]["physics"] = { "impact", "puncture", "slash" };
    effectJson["weapon"]["damage"]["elemental"] = { "heat", "cold", "electricity", "toxin", "blast", "radiation", "gas", "magnetic", "viral", "corrosive" };
    effectJson["weapon"]["damage"]["faction"] = { "greener", "corpus", "infested", "corrupted", "murmur", "sentientMultiplier" };
    effectJson["weapon"]["damage"]["other"] = { "baseDamage", "fireRate", "reloadTime", "criticalChance", "criticalDamage", "statusChance", "statusDuration", "multishot", "punchThrough", "attackSpeed", "followThrough", "range", "finisherDamage", "groundSlamDamage" };
    effectJson["warframe"]["stats"] = { "health", "armor", "shield", "shieldRechargeRate", "energy", "speed", "energyRegeneration" };
    effectJson["warframe"]["abilityStats"] = { "range", "duration", "strengh", "efficiency", "castingSpeed" };
    effectJson["warframe"]["utility"] = { "knockdownResistance", "knockdownRecoverySpeed", "aimGlideduration", "wallLatchDuration", "slide", "friction", "bulletJump", "enemyRadar" };
    effectJson["warframe"]["damageResistance"] = { "flatDR", "tauDR", "impactDR", "punctureDR", "slashDR", "heatDR", "coldDR", "electricityDR", "toxinDR", "blastDR", "radiationDR", "gasDR", "magneticDR", "viralDR", "corrosiveDR" };


    //horizontalisation
    for (int i = 0; i < effectJson["weapon"]["utiliy"].size(); i++)
    {
        effectTable.insert({ effectJson["weapon"]["utiliy"][i], 0 });
    }
    for (auto& a : effectJson["weapon"]["damage"])
    {
        for (auto& b : a)
        {
            effectTable.insert({ b, 0 });
        }
    }
    for (auto& a : effectJson["warframe"])
    {
        for (auto& b : a)
        {
            effectTable.insert({ b, 0 });
        }
    }
}



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



SetMod::SetMod()
{
    uniqueName = "";
    numUpgradesInSet = 0;
    stats = {};
}
SetMod::SetMod(nlohmann::json Json)
{
    try
    {
        uniqueName = Json["uniqueName"];
        numUpgradesInSet = Json["numUpgradesInSet"];
        stats = {};
        for (int i = 0; i < Json["stats"].size() ; i++)
        {
            stats.push_back(Json["stats"][i]);
        }
    }
    catch (...)
    {
        uniqueName = "";
        numUpgradesInSet = 0;
        stats = {};
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
        std::cout << "   n�" << i << std::endl;
        std::cout << "   " << cleanRetourChariot(description[i]) << std::endl;
    }
    std::cout << "subtype: " << subtype << std::endl;
    std::cout << "levelStats: " << std::endl;
    for (auto& a : levelStats)
    {
        std::cout << "   n�" << std::endl;
        for (auto& b : a)
        {
            std::cout << "      -" << cleanRetourChariot(b) << std::endl;
        }
    }
    std::cout << "modSet: " << modSet << std::endl;
}


void SetMod::debugDisplayData()
{
    std::cout << std::endl;
    std::cout << "[Debug Display Data]" << std::endl;
    std::cout << "uniqueName: " << uniqueName << std::endl;
    std::cout << "numUpgradesInSet: " << numUpgradesInSet << std::endl;
    std::cout << "stats: " << std::endl;
    for (auto& a : stats)
    {
        std::cout << "   -" << cleanRetourChariot(a) << std::endl;
    }
}


void EffectMod::debugDisplayData()
{
    std::cout << std::endl;
    std::cout << "[Debug Display Data]" << std::endl;
    for (auto& couple : effectTable)
    {
        std::cout << "   " << couple.first << ": " << couple.second << std::endl;
    }
}