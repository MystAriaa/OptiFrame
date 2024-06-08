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
    int t_slot)
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
}

PrimaryWeaponAttribute::PrimaryWeaponAttribute(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["codexSecret"], Json["damagePerShot"], Json["totalDamage"], Json["description"], Json["criticalChance"],
        Json["criticalMultiplier"], Json["procChance"], Json["fireRate"], Json["masteryReq"], Json["productCategory"], Json["slot"]);
    accuracy = Json["accuracy"];
    omegaAttenuation = Json["omegaAttenuation"];
    noise = Json["noise"];
    trigger = Json["trigger"];
    magasineSize = Json["magasineSize"];
    reloadTime = Json["reloadTime"];
    multishot = Json["multishot"];
}

SecondaryWeaponAttribute::SecondaryWeaponAttribute(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["codexSecret"], Json["damagePerShot"], Json["totalDamage"], Json["description"], Json["criticalChance"],
        Json["criticalMultiplier"], Json["procChance"], Json["fireRate"], Json["masteryReq"], Json["productCategory"], Json["slot"]);
    accuracy = Json["accuracy"];
    omegaAttenuation = Json["omegaAttenuation"];
    noise = Json["noise"];
    trigger = Json["trigger"];
    magasineSize = Json["magasineSize"];
    reloadTime = Json["reloadTime"];
    multishot = Json["multishot"];
}

MeleeWeaponAttribute::MeleeWeaponAttribute(nlohmann::json Json)
{
    loadData(Json["uniqueName"], Json["name"], Json["codexSecret"], Json["damagePerShot"], Json["totalDamage"], Json["description"], Json["criticalChance"],
        Json["criticalMultiplier"], Json["procChance"], Json["fireRate"], Json["masteryReq"], Json["productCategory"], Json["slot"]);
    omegaAttenuation = Json["omegaAttenuation"];
    float blockingAngle = Json["blockingAngle"];
    float comboDuration = Json["comboDuration"];
    float followThrough = Json["followThrough"];
    float range = Json["range"];
    float slamAttack = Json["slamAttack"];
    float slamRadialDamage = Json["slamRadialDamage"];
    float slamRadius = Json["slamRadius"];
    float slideAttack = Json["slideAttack"];
    float heavyAttackDamage = Json["heavyAttackDamage"];
    float heavySlamAttack = Json["heavySlamAttack"];
    float heavySlamRadialDamage = Json["heavySlamRadialDamage"];
    float heavySlamRadius = Json["heavySlamRadius"];
    float windUp = Json["windUp"];
}
