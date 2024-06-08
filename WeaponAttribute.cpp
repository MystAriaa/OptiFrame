#include "WeaponAttribute.hpp"

void WeaponAttribute::loadData(
    std::string t_name,
    std::string t_uniqueName,
    bool t_codexSecret,
    std::vector<float> t_damagePerShot,
    int t_totalDamage,
    std::string t_description,
    float t_criticalChance,
    float t_criticalMultiplier,
    float t_procChance,
    float t_fireRate,
    int t_masteryReq,
    std::string t_productCategory,
    int t_slot,
    float t_omegaAttenuation)
{
    uniqueName = t_uniqueName;
    name = t_name;
    codexSecret = t_codexSecret;
    damagePerShot = t_damagePerShot;
    totalDamage = t_totalDamage;
    description = t_description;
    criticalChance = t_criticalChance;
    criticalMultiplier = t_criticalMultiplier;
    procChance = t_procChance;
    fireRate = t_fireRate;
    masteryReq = t_masteryReq;
    productCategory = t_productCategory;
    slot = t_slot;
    omegaAttenuation = t_omegaAttenuation;
}

PrimaryWeaponAttribute::PrimaryWeaponAttribute(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["codexSecret"], Json["damagePerShot"], Json["totalDamage"], Json["description"], Json["criticalChance"],
        Json["criticalMultiplier"], Json["procChance"], Json["fireRate"], Json["masteryReq"], Json["productCategory"], Json["slot"], Json["omegaAttenuation"]);
    accuracy = Json["accuracy"];
    noise = Json["noise"];
    trigger = Json["trigger"];
    magasineSize = Json["magasineSize"];
    reloadTime = Json["reloadTime"];
    multishot = Json["multishot"];
}

SecondaryWeaponAttribute::SecondaryWeaponAttribute(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["codexSecret"], Json["damagePerShot"], Json["totalDamage"], Json["description"], Json["criticalChance"],
        Json["criticalMultiplier"], Json["procChance"], Json["fireRate"], Json["masteryReq"], Json["productCategory"], Json["slot"], Json["omegaAttenuation"]);
    accuracy = Json["accuracy"];
    noise = Json["noise"];
    trigger = Json["trigger"];
    magasineSize = Json["magasineSize"];
    reloadTime = Json["reloadTime"];
    multishot = Json["multishot"];
}

MeleeWeaponAttribute::MeleeWeaponAttribute(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["codexSecret"], Json["damagePerShot"], Json["totalDamage"], Json["description"], Json["criticalChance"],
        Json["criticalMultiplier"], Json["procChance"], Json["fireRate"], Json["masteryReq"], Json["productCategory"], Json["slot"], Json["omegaAttenuation"]);
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















//--------------------------------------
// Debug methodes

void WeaponAttribute::debugDisplayData()
{
    std::cout << std::endl;
    std::cout << "[Debug Display Data]" << std::endl;
    std::cout << "uniqueName: " << uniqueName << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "codexSecret: " << codexSecret << std::endl;
    std::cout << "damagePerShot: ";
    for (int i = 0; i < damagePerShot.size(); i++)
    {
        std::cout << "   " << damagePerShot[i] << std::endl;
    }
    std::cout << std::endl;
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
}

void PrimaryWeaponAttribute::debugDisplayData()
{
    WeaponAttribute::debugDisplayData();
    std::cout << "accuracy: " << accuracy << std::endl;
    std::cout << "noise: " << noise << std::endl;
    std::cout << "trigger: " << trigger << std::endl;
    std::cout << "magasineSize: " << magasineSize << std::endl;
    std::cout << "reloadTime: " << reloadTime << std::endl;
    std::cout << "multishot: " << multishot << std::endl;
}

void SecondaryWeaponAttribute::debugDisplayData()
{
    WeaponAttribute::debugDisplayData();
    std::cout << "accuracy: " << accuracy << std::endl;
    std::cout << "noise: " << noise << std::endl;
    std::cout << "trigger: " << trigger << std::endl;
    std::cout << "magasineSize: " << magasineSize << std::endl;
    std::cout << "reloadTime: " << reloadTime << std::endl;
    std::cout << "multishot: " << multishot << std::endl;
}

void MeleeWeaponAttribute::debugDisplayData()
{
    WeaponAttribute::debugDisplayData();
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