#include <string>
#include <vector>
#include <json.hpp>

class WeaponAttribute {
public:
    std::string name;
    std::string uniqueName;
    bool codexSecret;
    std::vector<float> damagePerShot;
    int totalDamage;
    std::string description;
    float criticalChance;
    float criticalMultiplier;
    float procChance;
    float fireRate;
    int masteryReq;
    std::string productCategory;
    int slot;

    WeaponAttribute();
    ~WeaponAttribute();

    void loadData(std::string t_name,
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
        int t_slot);
};

class PrimaryWeaponAttribute : public WeaponAttribute {
    using WeaponAttribute::WeaponAttribute;
public:
    float accuracy;
    float omegaAttenuation;
    std::string noise;
    std::string trigger;
    int magasineSize;
    float reloadTime;
    float multishot;

    PrimaryWeaponAttribute(nlohmann::json);
    ~PrimaryWeaponAttribute();
};

class SecondaryWeaponAttribute : public WeaponAttribute {
    using WeaponAttribute::WeaponAttribute;
public:
    float accuracy;
    float omegaAttenuation;
    std::string noise;
    std::string trigger;
    int magasineSize;
    float reloadTime;
    float multishot;

    SecondaryWeaponAttribute(nlohmann::json);
    ~SecondaryWeaponAttribute();
};

class MeleeWeaponAttribute : public WeaponAttribute {
    using WeaponAttribute::WeaponAttribute;
public:
    float omegaAttenuation;
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

    MeleeWeaponAttribute(nlohmann::json);
    ~MeleeWeaponAttribute();
};