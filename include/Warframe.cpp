#include "Warframe.hpp"

Suit::Suit()
{
    armor = 0;
    codexSecret = 0;
    description = "";
    health = 0;
    masteryReq = 0;
    name = "blankSuitName";
    parentName = "";
    passiveDescription = "";
    power = 0;
    productCategory = "";
    shield = 0;
    sprintSpeed = 0;
    stamina = 0;
    uniqueName = "blankSuitUniqueName";
    exalted = {};
    abilities = {};
}
Suit::Suit(nlohmann::json Json)
{
    try
    {
        armor = Json["armor"];
        codexSecret = Json["codexSecret"];
        description = Json["description"];
        health = Json["health"];
        masteryReq = Json["masteryReq"];
        name = Json["name"];
        parentName = Json["parentName"];
        if (Json.contains("passiveDescription")) { passiveDescription = Json["passiveDescription"]; } else { passiveDescription = ""; }
        power = Json["power"];
        productCategory = Json["productCategory"];
        shield = Json["shield"];
        sprintSpeed = Json["sprintSpeed"];
        stamina = Json["stamina"];
        uniqueName = Json["uniqueName"];

        exalted = {};
        if (Json.contains("exalted"))
        {
            for (int i = 0; i < Json["exalted"].size(); i++)
            {
                exalted.push_back(Json["exalted"][i]);
            }
        }

        abilities = {};
        for (int i = 0; i < Json["abilities"].size(); i++)
        {
            Ability tempAbility(Json["abilities"][i]["abilityName"], Json["abilities"][i]["abilityUniqueName"], Json["abilities"][i]["description"]);
            abilities.push_back(tempAbility);
        }
    }
    catch (...)
    {
        armor = 0;
        codexSecret = 0;
        description = "";
        health = 0;
        masteryReq = 0;
        name = "blankSuitName";
        parentName = "";
        passiveDescription = "";
        power = 0;
        productCategory = "";
        shield = 0;
        sprintSpeed = 0;
        stamina = 0;
        uniqueName = "blankSuitUniqueName";
        exalted = {};
        abilities = {};
        std::cout << "Error initializing Suit object, default object initialized instead." << std::endl;
    }
}





//--------------------------------------
// Debug methodes

void Suit::debugDisplayData()
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

    std::cout << "exalted: " << std::endl;
    for (int i = 0; i < exalted.size(); i++)
    {
        std::cout << "   n°" << i << std::endl;
        std::cout << "   " << cleanRetourChariot(exalted[i]) << std::endl;
    }
}