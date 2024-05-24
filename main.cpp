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
        std::cout << "Unable to open indexLzma";
        return 1;
    }
    std::cout << "LZMA file saved succesfully." << std::endl;
    

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
                std::cout << "Successfully decompressed.";
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






	return 0;

}