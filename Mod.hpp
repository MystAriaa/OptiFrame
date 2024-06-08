#include <string>
#include <vector>
#include <json.hpp>

class Mod {
public:
    std::string uniqueName;
    std::string name;
    std::string polarity;
    std::string rarity;
    bool codexSecret;
    int baseDrain;
    int fusionLimit;
    std::string compatName;
    std::string type;

    Mod() {};
    ~Mod() {};

    void loadData(
        std::string t_uniqueName,
        std::string t_name,
        std::string t_polarity,
        std::string t_rarity,
        bool t_codexSecret,
        int t_baseDrain,
        int t_fusionLimit,
        std::string t_compatName,
        std::string t_type);
};

class AuraMod : public Mod {
    using Mod::Mod;
public:
    std::vector<std::string> levelStats;

    AuraMod(nlohmann::json Json);
    ~AuraMod() {};
};

class WarframeMod : public Mod {
    using Mod::Mod;
public:
    std::vector<std::string> levelStats;

    WarframeMod(nlohmann::json Json) {};
    ~WarframeMod() {};
};

class StanceMod : public Mod {
    using Mod::Mod;
public:
    std::string description;

    StanceMod(nlohmann::json Json) {};
    ~StanceMod() {};
};

class MeleeMod : public Mod {
    using Mod::Mod;
public:
    std::vector<std::string> levelStats;

    MeleeMod(nlohmann::json Json) {};
    ~MeleeMod() {};
};

class PrimaryMod : public Mod {
    using Mod::Mod;
public:
    std::vector<std::string> levelStats;

    PrimaryMod(nlohmann::json Json) {};
    ~PrimaryMod() {};
};

class SecondaryMod : public Mod {
    using Mod::Mod;
public:
    std::vector<std::string> levelStats;

    SecondaryMod(nlohmann::json Json) {};
    ~SecondaryMod() {};
};