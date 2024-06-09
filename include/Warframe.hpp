#include <string>
#include <vector>
#include <json.hpp>
#include <iostream>
#include "Ability.hpp"
#include "usefullFunction.hpp"

class Suit {
public:
    std::string uniqueName;
    std::string name;
    std::string parentName;
    std::string description;
    int health;
    int shield;
    int armor;
    int stamina;
    int power;
    bool codexSecret;
    int masteryReq;
    float sprintSpeed;
    std::string passiveDescription;
    std::vector<std::string> exalted;
    std::vector<Ability> abilities;
    std::string productCategory;

    Suit();
    Suit(nlohmann::json Json);
    ~Suit() {};

    void debugDisplayData();
};