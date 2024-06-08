#include <string>
#include <vector>
#include <json.hpp>

class Ability {
public:
    std::string description;
    std::string abilityName;
    std::string abilityUniqueName;

    Ability(std::string t_abilityName, std::string t_abilityUniqueName, std::string t_description);
    ~Ability();
};