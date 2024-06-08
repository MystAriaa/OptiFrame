#include <string>
#include <vector>
#include <json.hpp>
#include "Ability.hpp"

class Warframe {
public:
    std::vector<Ability> abilities;
    int armor;
    bool codexSecret;
    std::string description;
    std::vector<std::string> exalted;
    int health;
    int masteryReq;
    std::string name;
    std::string parentName;
    std::string passiveDescription;
    int power;
    std::string productCategory;
    int shield;
    float sprintSpeed;
    int stamina;
    std::string uniqueName;

    Warframe(nlohmann::json Json);
    ~Warframe();


};