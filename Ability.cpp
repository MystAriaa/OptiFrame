#include "Ability.hpp"

Ability::Ability(std::string t_abilityName, std::string t_abilityUniqueName, std::string t_description)
{
	description = t_description;
	abilityName = t_abilityName;
	abilityUniqueName = t_abilityUniqueName;
}