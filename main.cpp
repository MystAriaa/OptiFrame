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

#include <sciplot/sciplot.hpp>
#include <cpr/cpr.h>
#include "json.hpp"
#include "pocketlzma.hpp"

using json = nlohmann::json;



//--------------------------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------------------------







int main()
{
    //------------------------------------------------------------------------------------------------------
	//API WARFRAME PUBLIC EXPORT
    // 
	//Get version index LZMA file
    std::cout << "Start of GET request ..." << std::endl;
	std::string url_index = "https://origin.warframe.com/PublicExport/index_en.txt.lzma";

    cpr::Response r = cpr::Get(cpr::Url{ url_index });
    std::cout << "Status code: " << r.status_code << '\n';
    std::cout << "End of GET request." << std::endl;
    std::cout << "Saving LZMA file locally ..." << std::endl;
    std::ofstream indexLzma("json/indexLzma.txt.lzma", std::ios::out | std::ios::binary);
    if (indexLzma.is_open())
    {
        for (std::size_t i = 0; i < r.text.size(); ++i)
        {
            indexLzma.write((&r.text.c_str()[i]), sizeof(r.text.c_str()[i]));
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


    //




	return 0;

}