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
#include <pocketlzma.hpp>

#include <usefullFunction.hpp>
#include <Mod.hpp>
#include <WeaponAttribute.hpp>
#include <Warframe.hpp>
#include <Arcane.hpp>


using Json = nlohmann::json;








//--------------------------------------------------------------------------------------------------------------------

Json loadJsonFromFile(std::string path)
{
    Json dataJson;
    std::ifstream dataStream(path);
    if (dataStream.is_open())
    {
        std::cout << "Loading " << path << std::endl;
        dataJson << dataStream;
        dataStream.close();
        std::cout << "Loaded " << path << std::endl;
        return dataJson;
    }
    else
    {
        std::cout << "Unable to open " << path << std::endl;
        return 1;
    }
}











//--------------------------------------------------------------------------------------------------------------------


int main()
{
    // Init
    std::filesystem::create_directories("./data");
    std::filesystem::create_directories("./data/json");
    std::filesystem::create_directories("./data/lzma");
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
    std::ofstream indexLzma("./data/lzma/indexLzma.txt.lzma", std::ios::out | std::ios::binary);
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
    std::string path = "./data/lzma/indexLzma.txt.lzma";
    std::vector<uint8_t> data;
    std::vector<uint8_t> decompressedData;
    plz::FileStatus fileStatus = plz::File::FromFile(path, data);
    if (fileStatus.status() == plz::FileStatus::Code::Ok)
    {
        plz::PocketLzma p;
        plz::StatusCode status = p.decompress(data, decompressedData);
        if (status == plz::StatusCode::Ok)
        {
            std::string outputPath = "./data/lzma/indexLzmaDecompressed.txt";
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
    std::string Weapon_Index, Warframe_Index, Upgrade_Index, RelicArcane_Index;
    std::string line;
    std::ifstream indexLzmaDecompressed("./data/lzma/indexLzmaDecompressed.txt", std::ios::in);
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
            if (lineF.find("ExportRelicArcane") != std::string::npos)
            {
                RelicArcane_Index = lineF;
            }
        }
    }
    else
    {
        std::cout << "Unable to open indexLzmaDecompressed" << std::endl;
        return 1;
    }

    if (!Weapon_Index.empty() && !Warframe_Index.empty() && !Upgrade_Index.empty() && !RelicArcane_Index.empty())
    {
        std::cout << "Weapon_Index: " << Weapon_Index << std::endl;
        std::cout << "Warframe_Index: " << Warframe_Index << std::endl;
        std::cout << "Upgrade_Index: " << Upgrade_Index << std::endl;
        std::cout << "RelicArcane_Index: " << RelicArcane_Index << std::endl;
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
    std::cout << "Get weapon JSON. " << std::endl;
    cpr::Response weaponResponse = cpr::Get(cpr::Url{ Base_URL+Weapon_Index });
    std::cout << "weaponResponse status code: " << weaponResponse.status_code << '\n';
    std::cout << "Get warframe JSON. " << std::endl;
    cpr::Response warframeResponse = cpr::Get(cpr::Url{ Base_URL + Warframe_Index });
    std::cout << "warframeResponse status code: " << warframeResponse.status_code << '\n';
    std::cout << "Get upgrade JSON. " << std::endl;
    cpr::Response upgradeResponse = cpr::Get(cpr::Url{ Base_URL + Upgrade_Index });
    std::cout << "upgradeResponse status code: " << upgradeResponse.status_code << '\n';
    std::cout << "Get relicArcane JSON. " << std::endl;
    cpr::Response relicArcaneResponse = cpr::Get(cpr::Url{ Base_URL + RelicArcane_Index });
    std::cout << "relicArcaneResponse status code: " << relicArcaneResponse.status_code << '\n';

    
    //Cleaning Response
    std::cout << "Start cleaning responses." << std::endl;
    std::cout << "weaponResponse ..." << std::endl;
    std::string cleanWeaponResponse = weaponResponse.text;
    while (cleanWeaponResponse.find("\r") != std::string::npos)
    {
        cleanWeaponResponse.replace(cleanWeaponResponse.find("\r"), 2, "");
    }
    std::cout << "warframeResponse ..." << std::endl;
    std::string cleanWarframeResponse = warframeResponse.text;
    while (cleanWarframeResponse.find("\r") != std::string::npos)
    {
        cleanWarframeResponse.replace(cleanWarframeResponse.find("\r"), 2, "");
    }
    std::cout << "upgradeResponse ..." << std::endl;
    std::string cleanUpgradeResponse = upgradeResponse.text;
    while (cleanUpgradeResponse.find("\r") != std::string::npos)
    {
        cleanUpgradeResponse.replace(cleanUpgradeResponse.find("\r"), 2, "");
    }
    std::cout << "relicArcaneResponse ..." << std::endl;
    std::string cleanRelicArcaneResponse = relicArcaneResponse.text;
    while (cleanRelicArcaneResponse.find("\r") != std::string::npos)
    {
        cleanRelicArcaneResponse.replace(cleanRelicArcaneResponse.find("\r"), 2, "");
    }
    std::cout << "Responses clean." << std::endl;


    //Save Response to JSON files
    std::cout << "Save responses to JSON files" << std::endl;
    std::cout << "Saving weaponResponse ..." << std::endl;
    std::ofstream weaponJSONstream("./data/json/weaponJson.json", std::ios::out );
    if (weaponJSONstream.is_open())
    {
        weaponJSONstream << std::setw(4) << Json::parse(cleanWeaponResponse) << std::endl;
        weaponJSONstream.close();
    }
    else
    {
        std::cout << "Unable to open weaponJSON" << std::endl;
        return 1;
    }
    std::cout << "Saving warframeResponse ..." << std::endl;
    std::ofstream warframeJSONstream("./data/json/warframeJson.json", std::ios::out);
    if (warframeJSONstream.is_open())
    {
        warframeJSONstream << std::setw(4) << Json::parse(cleanWarframeResponse) << std::endl;
        warframeJSONstream.close();
    }
    else
    {
        std::cout << "Unable to open warframeJSON" << std::endl;
        return 1;
    }
    std::cout << "Saving upgradeResponse ..." << std::endl;
    std::ofstream upgradeJSONstream("./data/json/upgradeJson.json", std::ios::out);
    if (upgradeJSONstream.is_open())
    {
        upgradeJSONstream << std::setw(4) << Json::parse(cleanUpgradeResponse) << std::endl;
        upgradeJSONstream.close();
    }
    else
    {
        std::cout << "Unable to open upgradeJSON" << std::endl;
        return 1;
    }
    std::cout << "Saving relicArcaneResponse ..." << std::endl;
    std::ofstream relicArcaneJSONstream("./data/json/relicArcaneJson.json", std::ios::out);
    if (relicArcaneJSONstream.is_open())
    {
        relicArcaneJSONstream << std::setw(4) << Json::parse(cleanRelicArcaneResponse) << std::endl;
        relicArcaneJSONstream.close();
    }
    else
    {
        std::cout << "Unable to open relicArcaneJSON" << std::endl;
        return 1;
    }
    std::cout << "Successfully saved." << std::endl;


    //Read 4 Interesting Json (Weapon/Warframe/Upgrade/RelicArcane)
    std::cout << "Start Jsons atomization & sorting ..." << std::endl;
    //Read Weapon Json
    std::cout << "weaponJson ..." << std::endl;
    Json weaponJson;
    std::ifstream weaponJsonstream("./data/json/weaponJson.json");
    if (weaponJsonstream.is_open())
    {
        weaponJsonstream >> weaponJson;
        weaponJsonstream.close();
    }
    else
    {
        std::cout << "Failed to load weaponJson." << std::endl;
    }
    //Save Each weapon data in a Json file sorted in their respectiv folder;
    for (int i = 0; i < weaponJson["ExportWeapons"].size(); i++)
    {
        if (!weaponJson["ExportWeapons"][i]["productCategory"].empty())
        {
            std::string tempPathString = "./data/json/weapons/";
            tempPathString.append(weaponJson["ExportWeapons"][i]["productCategory"]);
            std::filesystem::create_directories(tempPathString);

            tempPathString.append("/");
            tempPathString.append(clean_string_symbols(weaponJson["ExportWeapons"][i]["name"]));
            tempPathString.append(".json");

            std::ofstream tempFileStream(tempPathString);
            if (tempFileStream.is_open())
            {
                tempFileStream << std::setw(4) << weaponJson["ExportWeapons"][i];
                tempFileStream.close();
            }
        }
    }
    std::cout << "weaponJson successfully atomized." << std::endl;

    //Read Warframe Json
    std::cout << "warframeJson ..." << std::endl;
    Json warframeJson;
    std::ifstream warframeJsonstream("./data/json/warframeJson.json");
    if (warframeJsonstream.is_open())
    {
        warframeJsonstream >> warframeJson;
        warframeJsonstream.close();
    }
    else
    {
        std::cout << "Failed to load warframeJson." << std::endl;
    }
    for (int i = 0; i < warframeJson["ExportWarframes"].size(); i++)
    {
        if (!warframeJson["ExportWarframes"][i]["productCategory"].empty())
        {
            std::string tempPathString = "./data/json/warframes/";
            tempPathString.append(warframeJson["ExportWarframes"][i]["productCategory"]);
            std::filesystem::create_directories(tempPathString);

            tempPathString.append("/");
            tempPathString.append(clean_string_symbols(warframeJson["ExportWarframes"][i]["name"]));
            tempPathString.append(".json");

            std::ofstream tempFileStream(tempPathString);
            if (tempFileStream.is_open())
            {
                tempFileStream << std::setw(4) << warframeJson["ExportWarframes"][i];
                tempFileStream.close();
            }
        }
    }
    std::cout << "warframeJson successfully atomized." << std::endl;

    //Read Upgrade Json
    std::cout << "upgradeJson ..." << std::endl;
    Json upgradeJson;
    std::ifstream upgradeJsonstream("./data/json/upgradeJson.json");
    if (upgradeJsonstream.is_open())
    {
        upgradeJsonstream >> upgradeJson;
        upgradeJsonstream.close();
    }
    else
    {
        std::cout << "Failed to load upgradeJson." << std::endl;
    }
    for (int i = 0; i < upgradeJson["ExportUpgrades"].size(); i++)
    {
        if (!upgradeJson["ExportUpgrades"][i]["type"].empty())
        {
            std::string tempPathString = "./data/json/upgrades/";
            tempPathString.append(upgradeJson["ExportUpgrades"][i]["type"]);
            std::filesystem::create_directories(tempPathString);

            tempPathString.append("/");
            tempPathString.append(clean_string_symbols(upgradeJson["ExportUpgrades"][i]["name"]));
            tempPathString.append(".json");

            std::ofstream tempFileStream(tempPathString);
            if (tempFileStream.is_open())
            {
                tempFileStream << std::setw(4) << upgradeJson["ExportUpgrades"][i];
                tempFileStream.close();
            }
        }
    }
    for (int i = 0; i < upgradeJson["ExportModSet"].size(); i++)
    {
        std::string tempPathString = "./data/json/upgrades/modSets/";
        std::filesystem::create_directories(tempPathString);
        tempPathString.append("/");
        std::vector<std::string> ff = split(upgradeJson["ExportModSet"][i]["uniqueName"],"/");
        tempPathString.append(ff[ff.size() - 1]);
        tempPathString.append(".json");

        std::ofstream tempFileStream(tempPathString);
        if (tempFileStream.is_open())
        {
            tempFileStream << std::setw(4) << upgradeJson["ExportModSet"][i];
            tempFileStream.close();
        }
    }
    
    //Read RelicArcane Json
    std::cout << "relicArcaneJson ..." << std::endl;
    Json relicArcaneJson;
    std::ifstream relicArcaneJsonstream("./data/json/relicArcaneJson.json");
    if (relicArcaneJsonstream.is_open())
    {
        relicArcaneJsonstream >> relicArcaneJson;
        relicArcaneJsonstream.close();
    }
    else
    {
        std::cout << "Failed to load relicArcaneJson." << std::endl;
    }
    for (int i = 0; i < relicArcaneJson["ExportRelicArcane"].size(); i++)
    {
        if (!relicArcaneJson["ExportRelicArcane"][i].contains("relicRewards") && relicArcaneJson["ExportRelicArcane"][i].contains("levelStats"))
        {
            std::string tempPathString = "./data/json/arcanes/";
            std::filesystem::create_directories(tempPathString);

            tempPathString.append(clean_string_symbols(relicArcaneJson["ExportRelicArcane"][i]["name"]));
            tempPathString.append(".json");

            std::ofstream tempFileStream(tempPathString);
            if (tempFileStream.is_open())
            {
                tempFileStream << std::setw(4) << relicArcaneJson["ExportRelicArcane"][i];
                tempFileStream.close();
            }
        }
    }
    std::cout << "upgradeJson successfully atomized." << std::endl;








    //---------------------------------------------------------------------------

    if (false)
    {
        //Test Mods
        Mod BriefRespite(loadJsonFromFile("./data/json/upgrades/AURA/Brief Respite.json"));
        BriefRespite.debugDisplayData();
        Mod CathodeCurrent(loadJsonFromFile("./data/json/upgrades/WARFRAME/Cathode Current.json"));
        CathodeCurrent.debugDisplayData();
        Mod BorealContempt(loadJsonFromFile("./data/json/upgrades/MELEE/Boreal's Contempt.json"));
        BorealContempt.debugDisplayData();
        Mod FailedCallMod(loadJsonFromFile(""));
        FailedCallMod.debugDisplayData();
        //Test SetMod
        SetMod Vigilante(loadJsonFromFile("./data/json/upgrades/modSets/VigilanteSetMod.json"));
        Vigilante.debugDisplayData();

        //Test Suits
        Suit WispPrime(loadJsonFromFile("./data/json/warframes/Suits/Wisp Prime.json"));
        WispPrime.debugDisplayData();
        Suit Itzal(loadJsonFromFile("./data/json/warframes/SpaceSuits/ARCHWING Itzal.json"));
        Itzal.debugDisplayData();
        Suit Voidrig(loadJsonFromFile("./data/json/warframes/MechSuits/Voidrig.json"));
        Voidrig.debugDisplayData();
        Suit FailedCallSuit("");
        FailedCallSuit.debugDisplayData();

        //Test Weapons
        GunWeaponAttribute Torid(loadJsonFromFile("./data/json/weapons/LongGuns/Torid.json"));
        Torid.debugDisplayData();
        GunWeaponAttribute KuvaBrakk(loadJsonFromFile("./data/json/weapons/Pistols/Kuva Brakk.json"));
        KuvaBrakk.debugDisplayData();
        MeleeWeaponAttribute Anku(loadJsonFromFile("./data/json/weapons/Melee/Anku.json"));
        Anku.debugDisplayData();
        GunWeaponAttribute FailedCallWeapon("");
        FailedCallWeapon.debugDisplayData();

        //Test Arcane
        Arcane Energize(loadJsonFromFile("./data/json/arcanes/Arcane Energize.json"));
        Energize.debugDisplayData();

        //Test EffectMod
        EffectMod defaultEffectMod;
        defaultEffectMod.debugDisplayData();
    }
    
    


	return 0;

}
