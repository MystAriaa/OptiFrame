#include <string>
#include <vector>
#include <json.hpp>
#include <iostream>

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
    std::vector<std::string> description;

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
        std::string t_type,
        std::vector<std::string> t_description);

    void debugDisplayData();
};

class AuraMod : public Mod {
public:
    std::vector<std::string> levelStats;

    AuraMod(nlohmann::json Json);
    ~AuraMod() {};

    void debugDisplayData();
};

class WarframeMod : public Mod {
public:
    std::vector<std::string> levelStats;

    WarframeMod(nlohmann::json Json);
    ~WarframeMod() {};

    void debugDisplayData();
};

class StanceMod : public Mod {
public:
    std::string description;

    StanceMod(nlohmann::json Json);
    ~StanceMod() {};

    void debugDisplayData();
};

class MeleeMod : public Mod {
public:
    std::vector<std::string> levelStats;

    MeleeMod(nlohmann::json Json);
    ~MeleeMod() {};

    void debugDisplayData();
};

class PrimaryMod : public Mod {
public:
    std::vector<std::string> levelStats;

    PrimaryMod(nlohmann::json Json);
    ~PrimaryMod() {};

    void debugDisplayData();
};

class SecondaryMod : public Mod {
public:
    std::vector<std::string> levelStats;

    SecondaryMod(nlohmann::json Json);
    ~SecondaryMod() {};

    void debugDisplayData();
};