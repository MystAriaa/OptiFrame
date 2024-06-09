#include "Ability.hpp"

Ability::Ability(std::string t_abilityName, std::string t_abilityUniqueName, std::string t_description)
{
	description = t_description;
	abilityName = t_abilityName;
	abilityUniqueName = t_abilityUniqueName;
}




//--------------------------------------
// Debug methodes

void Ability::debugDisplayData()
{
	std::cout << "   abilityName: " << abilityName << std::endl;
	std::cout << "   abilityUniqueName: " << abilityUniqueName << std::endl;
	std::cout << "   description: " << description << std::endl;
}