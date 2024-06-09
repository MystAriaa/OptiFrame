#include "WeaponAttribute.hpp"

DamagePerShotTable::DamagePerShotTable(std::vector<float> damagePerShot)
{
    damageTable = {};
    if (elementTable.size() == damagePerShot.size())
    {
        for (int i = 0; i < elementTable.size(); i++)
        {
            damageTable.insert({ elementTable[i],damagePerShot[i] });
        }
    }
    else
    {
        for (int i = 0; i < elementTable.size(); i++)
        {
            damageTable.insert({ elementTable[i],0 });
        }
    }
}

GunWeaponAttribute::GunWeaponAttribute()
{
    name = "blankName";
    uniqueName = "blankUniqueName";
    codexSecret = false;
    damagePerShot = {};
    totalDamage = 0;
    description = "";
    criticalChance = 0;
    criticalMultiplier = 0;
    procChance = 0;
    fireRate = 0;
    masteryReq = 0;
    productCategory = "";
    slot = 0;
    accuracy = 0;
    omegaAttenuation = 0;
    maxLevelCap = 0;
    noise = "";
    trigger = "";
    magazineSize = 0;
    reloadTime = 0;
    sentinel = false;
    multishot = 0;
}
GunWeaponAttribute::GunWeaponAttribute(nlohmann::json Json)
{
    try
    {
        name = Json["name"];
        uniqueName = Json["uniqueName"];
        codexSecret = Json["codexSecret"];
        std::vector<float> tempVector = {};
        for (int i = 0; i < Json["damagePerShot"].size(); i++)
        {
            tempVector.push_back(Json["damagePerShot"][i]);
        }
        DamagePerShotTable tempTable(tempVector);
        damagePerShot = tempTable;
        totalDamage = Json["totalDamage"];
        description = Json["description"];
        criticalChance = Json["criticalChance"];
        criticalMultiplier = Json["criticalMultiplier"];
        procChance = Json["procChance"];
        fireRate = Json["fireRate"];
        masteryReq = Json["masteryReq"];
        productCategory = Json["productCategory"];
        slot = Json["slot"];
        accuracy = Json["accuracy"];
        omegaAttenuation = Json["omegaAttenuation"];
        if (Json.contains("maxLevelCap")) { maxLevelCap = Json["maxLevelCap"]; }
        else { maxLevelCap = 30; }
        noise = Json["noise"];
        trigger = Json["trigger"];
        magazineSize = Json["magazineSize"];
        reloadTime = Json["reloadTime"];
        if (Json.contains("sentinel")) { sentinel = Json["sentinel"]; }
        else { sentinel = false; }
        multishot = Json["multishot"];
    }
    catch (...)
    {
        name = "blankName";
        uniqueName = "blankUniqueName";
        codexSecret = false;
        damagePerShot = {};
        totalDamage = 0;
        description = "";
        criticalChance = 0;
        criticalMultiplier = 0;
        procChance = 0;
        fireRate = 0;
        masteryReq = 0;
        productCategory = "";
        slot = 0;
        accuracy = 0;
        omegaAttenuation = 0;
        maxLevelCap = 0;
        noise = "";
        trigger = "";
        magazineSize = 0;
        reloadTime = 0;
        sentinel = false;
        multishot = 0;
        std::cout << "Error initializing GunWeaponAttribute object, default object initialized instead."<< std::endl;
    }
}

MeleeWeaponAttribute::MeleeWeaponAttribute()
{
    name = "blankName";
    uniqueName = "blankUniqueName";
    codexSecret = false;
    damagePerShot = {};
    totalDamage = 0;
    description = "";
    criticalChance = 0;
    criticalMultiplier = 0;
    procChance = 0;
    fireRate = 0;
    masteryReq = 0;
    productCategory = "";
    slot = 0;
    omegaAttenuation = 0;
    maxLevelCap = 0;
    blockingAngle = 0;
    comboDuration = 0;
    followThrough = 0;
    range = 0;
    slamAttack = 0;
    slamRadialDamage = 0;
    slamRadius = 0;
    slideAttack = 0;
    heavyAttackDamage = 0;
    heavySlamAttack = 0;
    heavySlamRadialDamage = 0;
    heavySlamRadius = 0;
    windUp = 0;
    std::cout << "Error initializing MeleeWeaponAttribute object, default object initialized instead." << std::endl;
}
MeleeWeaponAttribute::MeleeWeaponAttribute(nlohmann::json Json)
{
    try
    {
        name = Json["name"];
        uniqueName = Json["uniqueName"];
        codexSecret = Json["codexSecret"];
        std::vector<float> tempVector = {};
        for (int i = 0; i < Json["damagePerShot"].size(); i++)
        {
            tempVector.push_back(Json["damagePerShot"][i]);
        }
        DamagePerShotTable tempTable(tempVector);
        damagePerShot = tempTable;
        totalDamage = Json["totalDamage"];
        description = Json["description"];
        criticalChance = Json["criticalChance"];
        criticalMultiplier = Json["criticalMultiplier"];
        procChance = Json["procChance"];
        fireRate = Json["fireRate"];
        masteryReq = Json["masteryReq"];
        productCategory = Json["productCategory"];
        codexSecret = Json["codexSecret"];
        slot = Json["slot"];
        omegaAttenuation = Json["omegaAttenuation"];
        if (Json.contains("maxLevelCap")) { maxLevelCap = Json["maxLevelCap"]; }
        else { maxLevelCap = 30; }
        blockingAngle = Json["blockingAngle"];
        comboDuration = Json["comboDuration"];
        followThrough = Json["followThrough"];
        range = Json["range"];
        slamAttack = Json["slamAttack"];
        slamRadialDamage = Json["slamRadialDamage"];
        slamRadius = Json["slamRadius"];
        slideAttack = Json["slideAttack"];
        heavyAttackDamage = Json["heavyAttackDamage"];
        heavySlamAttack = Json["heavySlamAttack"];
        heavySlamRadialDamage = Json["heavySlamRadialDamage"];
        heavySlamRadius = Json["heavySlamRadius"];
        windUp = Json["windUp"];
    }
    catch (...)
    {
        name = "blankName";
        uniqueName = "blankUniqueName";
        codexSecret = false;
        damagePerShot = {};
        totalDamage = 0;
        description = "";
        criticalChance = 0;
        criticalMultiplier = 0;
        procChance = 0;
        fireRate = 0;
        masteryReq = 0;
        productCategory = "";
        slot = 0;
        omegaAttenuation = 0;
        maxLevelCap = 0;
        blockingAngle = 0;
        comboDuration = 0;
        followThrough = 0;
        range = 0;
        slamAttack = 0;
        slamRadialDamage = 0;
        slamRadius = 0;
        slideAttack = 0;
        heavyAttackDamage = 0;
        heavySlamAttack = 0;
        heavySlamRadialDamage = 0;
        heavySlamRadius = 0;
        windUp = 0;
        std::cout << "Error initializing MeleeWeaponAttribute object, default object initialized instead." << std::endl;
    }
}















//--------------------------------------
// Debug methodes

void DamagePerShotTable::debugDisplayData()
{
    for (auto& couple : damageTable)
    {
        std::cout << "   " << couple.first << ": " << couple.second << std::endl;
    }
}

void GunWeaponAttribute::debugDisplayData()
{
    std::cout << std::endl;
    std::cout << "[Debug Display Data]" << std::endl;
    std::cout << "uniqueName: " << uniqueName << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "codexSecret: " << codexSecret << std::endl;
    std::cout << "damagePerShot: " << std::endl;
    damagePerShot.debugDisplayData();
    std::cout << "totalDamage: " << totalDamage << std::endl;
    std::cout << "description: " << description << std::endl;
    std::cout << "criticalChance: " << criticalChance << std::endl;
    std::cout << "criticalMultiplier: " << criticalMultiplier << std::endl;
    std::cout << "procChance: " << procChance << std::endl;
    std::cout << "fireRate: " << fireRate << std::endl;
    std::cout << "masteryReq: " << masteryReq << std::endl;
    std::cout << "productCategory: " << productCategory << std::endl;
    std::cout << "slot: " << slot << std::endl;
    std::cout << "accuracy: " << accuracy << std::endl;
    std::cout << "omegaAttenuation: " << omegaAttenuation << std::endl;
    std::cout << "maxLevelCap: " << maxLevelCap << std::endl;
    std::cout << "noise: " << noise << std::endl;
    std::cout << "trigger: " << trigger << std::endl;
    std::cout << "magazineSize: " << magazineSize << std::endl;
    std::cout << "reloadTime: " << reloadTime << std::endl;
    std::cout << "sentinel: " << sentinel << std::endl;
    std::cout << "multishot: " << multishot << std::endl;
}

void MeleeWeaponAttribute::debugDisplayData()
{
    std::cout << std::endl;
    std::cout << "[Debug Display Data]" << std::endl;
    std::cout << "uniqueName: " << uniqueName << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "codexSecret: " << codexSecret << std::endl;
    std::cout << "damagePerShot: " << std::endl;
    damagePerShot.debugDisplayData();
    std::cout << "totalDamage: " << totalDamage << std::endl;
    std::cout << "description: " << description << std::endl;
    std::cout << "criticalChance: " << criticalChance << std::endl;
    std::cout << "criticalMultiplier: " << criticalMultiplier << std::endl;
    std::cout << "procChance: " << procChance << std::endl;
    std::cout << "fireRate: " << fireRate << std::endl;
    std::cout << "masteryReq: " << masteryReq << std::endl;
    std::cout << "productCategory: " << productCategory << std::endl;
    std::cout << "slot: " << slot << std::endl;
    std::cout << "omegaAttenuation: " << omegaAttenuation << std::endl;
    std::cout << "maxLevelCap: " << maxLevelCap << std::endl;
    std::cout << "blockingAngle: " << blockingAngle << std::endl;
    std::cout << "comboDuration: " << comboDuration << std::endl;
    std::cout << "followThrough: " << followThrough << std::endl;
    std::cout << "range: " << range << std::endl;
    std::cout << "slamAttack: " << slamAttack << std::endl;
    std::cout << "slamRadialDamage: " << slamRadialDamage << std::endl;
    std::cout << "slamRadius: " << slamRadius << std::endl;
    std::cout << "slideAttack: " << slideAttack << std::endl;
    std::cout << "heavyAttackDamage: " << heavyAttackDamage << std::endl;
    std::cout << "heavySlamAttack: " << heavySlamAttack << std::endl;
    std::cout << "heavySlamRadialDamage: " << heavySlamRadialDamage << std::endl;
    std::cout << "heavySlamRadius: " << heavySlamRadius << std::endl;
    std::cout << "windUp: " << windUp << std::endl;
}