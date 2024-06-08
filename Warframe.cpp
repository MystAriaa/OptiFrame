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