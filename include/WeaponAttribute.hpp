#include <string>
#include <vector>
#include <json.hpp>
#include <iostream>
#include <unordered_map>
#include "usefullFunction.hpp"

class DamagePerShotTable {
public:
    std::vector<std::string> elementTable = { "Impact", "Puncture", "Slash", "Heat", "Cold", "Electricity", "Toxin", "Blast", "Radiation", "Gas", "Magnetic", "Viral", "Corrosive", "Void", "Tau", "DT_CINEMATIC", "DT_SHIELD_DRAIN", "DT_HEALTH_DRAIN", "DT_ENERGY_DRAIN", "True" };
    std::unordered_map<std::string, float> damageTable;

    DamagePerShotTable() {};
    DamagePerShotTable(std::vector<float> damagePerShot);
    ~DamagePerShotTable() {};

    void debugDisplayData();
};

class GunWeaponAttribute {
public:
    std::string name;
    std::string uniqueName;
    bool codexSecret;
    DamagePerShotTable damagePerShot;
    int totalDamage;
    std::string description;
    float criticalChance;
    float criticalMultiplier;
    float procChance;
    float fireRate;
    int masteryReq;
    std::string productCategory;
    int slot;
    float accuracy;
    float omegaAttenuation;
    int maxLevelCap;
    std::string noise;
    std::string trigger;
    int magazineSize;
    float reloadTime;
    bool sentinel;
    int multishot;

    GunWeaponAttribute();
    GunWeaponAttribute(nlohmann::json Json);
    ~GunWeaponAttribute() {};

    void debugDisplayData();
};


class MeleeWeaponAttribute {
public:
    std::string name;
    std::string uniqueName;
    bool codexSecret;
    DamagePerShotTable damagePerShot;
    int totalDamage;
    std::string description;
    float criticalChance;
    float criticalMultiplier;
    float procChance;
    float fireRate;
    int masteryReq;
    std::string productCategory;
    int slot;
    float omegaAttenuation;
    int maxLevelCap;
    float blockingAngle;
    float comboDuration;
    float followThrough;
    float range;
    float slamAttack;
    float slamRadialDamage;
    float slamRadius;
    float slideAttack;
    float heavyAttackDamage;
    float heavySlamAttack;
    float heavySlamRadialDamage;
    float heavySlamRadius;
    float windUp;

    MeleeWeaponAttribute();
    MeleeWeaponAttribute(nlohmann::json Json);
    ~MeleeWeaponAttribute() {};

    void debugDisplayData();
};