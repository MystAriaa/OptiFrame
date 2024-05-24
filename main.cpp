#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <streambuf>
#include <sstream>
#include <filesystem>

#include <sciplot/sciplot.hpp>
#include <cpr/cpr.h>
#include <json.hpp>
#include "pocketlzma.hpp"

using Json = nlohmann::json;



//--------------------------------------------------------------------------------------------------------------------

class PistolWeaponAttribute {
public:
    std::string name;
    std::string uniqueName;
    bool codexSecret;
    std::vector<float> damagePerShot;
    int totalDamage;
    std::string description;
    float criticalChance;
    float criticalMultiplier;
    float procChance;
    float fireRate;
    int masteryReq;
    std::string productCategory;
    int slot;
    float accuracy;
    float omegaAttenuation;
    std::string noise;
    std::string trigger;
    int magasineSize;
    float reloadTime;
    float multishot;
};

class MeleeWeaponAttribute {
public:
    std::string name;
    std::string uniqueName;
    bool codexSecret;
    std::vector<float> damagePerShot;
    int totalDamage;
    std::string description;
    float criticalChance;
    float criticalMultiplier;
    float procChance;
    float fireRate;
    int masteryReq;
    std::string productCategory;
    int slot;
    float omegaAttenuation;
    float blockingAngle;
    float comboDuration;
    float followThrough;
    float range;
    float slamAttack;
    float slamRadialDamage;
    float slamRadius;
    float slideAttack;
    float heavyAttackDamage;
    float heavySlamAttack;
    float heavySlamRadialDamage;
    float heavySlamRadius;
    float windUp;
};

//--------------------------------------------------------------------------------------------------------------------

std::string clean_string(std::string str)
{
    std::string c_str = str;
    c_str.erase(0, 1);
    c_str.erase(c_str.size() - 1);
    return c_str;
}






int main()
{
    //------------------------------------------------------------------------------------------------------
	//API WARFRAME PUBLIC EXPORT
    // 
	//Get version index LZMA file
    std::cout << "Start of GET request ..." << std::endl;
	std::string url_index = "https://origin.warframe.com/PublicExport/index_en.txt.lzma";

    cpr::Response indexResponse = cpr::Get(cpr::Url{ url_index });
    std::cout << "Status code: " << indexResponse.status_code << '\n';
    std::cout << "End of GET request." << std::endl;
    std::cout << "Saving LZMA file locally ..." << std::endl;
    std::ofstream indexLzma("json/indexLzma.txt.lzma", std::ios::out | std::ios::binary);
    if (indexLzma.is_open())
    {
        for (std::size_t i = 0; i < indexResponse.text.size(); ++i)
        {
            indexLzma.write((&indexResponse.text.c_str()[i]), sizeof(indexResponse.text.c_str()[i]));
        }
        indexLzma.close();
    }
    else
    {
        std::cout << "Unable to open indexLzma" << std::endl;
        return 1;
    }
    std::cout << "LZMA file saved succesfully." << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    

    //Decompress LZMA to txt
    std::cout << "Decompressing LZMA file ..." << std::endl;
    std::string path = "json/indexLzma.txt.lzma";
    std::vector<uint8_t> data;
    std::vector<uint8_t> decompressedData;
    plz::FileStatus fileStatus = plz::File::FromFile(path, data);
    if (fileStatus.status() == plz::FileStatus::Code::Ok)
    {
        plz::PocketLzma p;
        plz::StatusCode status = p.decompress(data, decompressedData);
        if (status == plz::StatusCode::Ok)
        {
            std::string outputPath = "json/indexLzmaDecompressed.txt";
            plz::FileStatus writeStatus = plz::File::ToFile(outputPath, decompressedData);
            if (writeStatus.status() == plz::FileStatus::Code::Ok)
            {
                std::cout << "Successfully decompressed." << std::endl;
            }
            else
            {
                std::cout << "Error, failed to decompress LZMA file, exiting." << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "Error, failed to decompress LZMA file, exiting." << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Error, failed to open LZMA file, exiting." << std::endl;
        return 1;
    }
    std::cout << "---------------------------------------" << std::endl;

    //Load Indexes Value
    std::cout << "Loading indexes ..." << std::endl;
    std::string Weapon_Index, Warframe_Index, Upgrade_Index;
    std::string line;
    std::ifstream indexLzmaDecompressed("json/indexLzmaDecompressed.txt", std::ios::in);
    if (indexLzmaDecompressed.is_open())
    {
        while (std::getline(indexLzmaDecompressed, line))
        {
            std::istringstream iss(line);
            std::string lineF;
            if (!(iss >> lineF)) { break; } // error

            if (lineF.find("ExportWeapons") != std::string::npos)
            {
                Weapon_Index = lineF;
            }
            if (lineF.find("ExportWarframes") != std::string::npos)
            {
                Warframe_Index = lineF;
            }
            if (lineF.find("ExportUpgrades") != std::string::npos)
            {
                Upgrade_Index = lineF;
            }
        }
    }
    else
    {
        std::cout << "Unable to open indexLzmaDecompressed" << std::endl;
        return 1;
    }

    if (!Weapon_Index.empty() && !Warframe_Index.empty() && !Upgrade_Index.empty())
    {
        std::cout << "Weapon_Index: " << Weapon_Index << std::endl;
        std::cout << "Warframe_Index: " << Warframe_Index << std::endl;
        std::cout << "Upgrade_Index: " << Upgrade_Index << std::endl;
    }
    else
    {
        std::cout << "Failed to read Indexes from file, exiting." << std::endl;
        return 1;
    }
    std::cout << "Indexes loaded successfully." << std::endl;
    std::cout << "---------------------------------------" << std::endl;


    //Load JSONs
    std::cout << "Start of GET requests (content.warframe.com/PublicExport/Manifest)" << std::endl;
    std::string Base_URL = "https://content.warframe.com/PublicExport/Manifest/";
    //Load Weapons Json
    std::cout << "Weapon JSON: " << std::endl;
    cpr::Response weaponResponse = cpr::Get(cpr::Url{ Base_URL+Weapon_Index });
    std::cout << "Status code: " << weaponResponse.status_code << '\n';
    std::ofstream weaponJSONstream("json/weaponJson.json", std::ios::out );
    std::string cleanResponse = weaponResponse.text;
    //Cleaning Json
    while (cleanResponse.find("\r") != std::string::npos)
    {
        cleanResponse.replace(cleanResponse.find("\r"), 2, "");
    }
    //Save Json
    if (weaponJSONstream.is_open())
    {
        weaponJSONstream << cleanResponse;
        weaponJSONstream.close();
    }
    else
    {
        std::cout << "Unable to open weaponJSON" << std::endl;
        return 1;
    }

    

    Json weaponJson;
    //Read Weapon Json
    std::ifstream weaponJsonstream("json/weaponJson.json");
    if (weaponJsonstream.is_open())
    {
        weaponJsonstream >> weaponJson;
        weaponJsonstream.close();
    }
    

    //Save Each weapon data in a Json file sorted in their respectiv folder;
    for (int i = 0; i < weaponJson["ExportWeapons"].size(); i++)
    {
        std::string tempPathString = "json/weapons/";
        tempPathString.append(weaponJson["ExportWeapons"][i]["productCategory"]);
        std::filesystem::create_directories(tempPathString);

        tempPathString.append("/");
        tempPathString.append(weaponJson["ExportWeapons"][i]["name"]);
        tempPathString.append(".json");

        
        std::ofstream tempFileStream(tempPathString);
        std::cout << tempPathString << std::endl;
        if (tempFileStream.is_open())
        {
            tempFileStream << weaponJson["ExportWeapons"][i];
            tempFileStream.close();
        }
    }


    //todo
    //ne pas faire les spawn de directory + file si il existe deja
    //delete les file ZLMA + masterWeaponJson quand try fini
    //comment








	return 0;

}