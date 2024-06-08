#include "Warframe.hpp"

Warframe::Warframe(nlohmann::json Json)
{
    std::vector<Ability> abilities;
    armor = Json["armor"];
    codexSecret = Json["codexSecret"];
    description = Json["description"];
    health = Json["health"];
    masteryReq = Json["masteryReq"];
    name = Json["name"];
    parentName = Json["parentName"];
    passiveDescription = Json["passiveDescription"];
    power = Json["power"];
    productCategory = Json["productCategory"];
    shield = Json["shield"];
    sprintSpeed = Json["sprintSpeed"];
    stamina = Json["stamina"];
    uniqueName = Json["uniqueName"];

    std::vector<std::string> tempVector1 = {};
    for (int i = 0; i < Json["exalted"].size(); i++)
    {
        tempVector1.push_back(Json["exalted"][i]);
    }
    exalted = tempVector1;

    std::vector<Ability> tempVector2 = {};
    for (int i = 0; i < Json["abilities"].size(); i++)
    {
        Ability tempAbility(Json["abilities"][i]["abilityName"], Json["abilities"][i]["abilityUniqueName"], Json["abilities"][i]["description"]);
        tempVector2.push_back(tempAbility);
    }
    abilities = tempVector2;
}





//--------------------------------------
// Debug methodes

void Warframe::debugDisplayData()
{
    std::cout << std::endl;
    std::cout << "[Debug Display Data]" << std::endl;
    std::cout << "uniqueName: " << uniqueName << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "armor: " << armor << std::endl;
    std::cout << "codexSecret: " << codexSecret << std::endl;
    std::cout << "description: " << description << std::endl;
    std::cout << "health: " << health << std::endl;
    std::cout << "masteryReq: " << masteryReq << std::endl;
    std::cout << "parentName: " << parentName << std::endl;
    std::cout << "passiveDescription: " << passiveDescription << std::endl;
    std::cout << "power: " << power << std::endl;
    std::cout << "productCategory: " << productCategory << std::endl;
    std::cout << "shield: " << shield << std::endl;
    std::cout << "sprintSpeed: " << sprintSpeed << std::endl;
    std::cout << "stamina: " << stamina << std::endl;

    std::cout << "abilities: " << std::endl;
    for (int i = 0; i < abilities.size(); i++)
    {
        std::cout << "   n°" << i << std::endl;
        abilities[i].debugDisplayData();
    }
}