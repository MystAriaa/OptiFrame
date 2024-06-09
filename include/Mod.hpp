#include <string>
#include <vector>
#include <json.hpp>
#include <iostream>
#include "usefullFunction.hpp"

class Mod {
public:
    std::string uniqueName;
    std::string name;
    std::string polarity;
    std::string rarity;
    bool codexSecret;
    int baseDrain;
    int fusionLimit;
    bool excludeFromCodex;
    bool isUtility;
    std::string compatName;
    std::string type;
    std::vector<std::string> description;
    std::string subtype;
    std::vector<std::vector<std::string>> levelStats;
    std::string modSet;

    Mod();
    Mod(nlohmann::json Json);
    ~Mod() {};

    void debugDisplayData();
};


class RivenMod {
public:
    std::string uniqueName;
    std::string name;
    std::string polarity;
    std::string rarity;
    bool codexSecret;
    int baseDrain;
    int fusionLimit;
    bool excludeFromCodex;
    nlohmann::json upgradeEntries; //will not use
    nlohmann::json availableChallenges; //will not use

    std::vector<std::vector<std::string>> levelStats;

    RivenMod();
    RivenMod(nlohmann::json Json);
    ~RivenMod() {};
};

class SetMod {
public:
    std::string uniqueName;
    int numUpgradesInSet;
    std::vector<std::string> stats;

    SetMod();
    SetMod(nlohmann::json Json);
    ~SetMod() {};

    void debugDisplayData();
};