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
	//get version index

	std::string url_index = "https://origin.warframe.com/PublicExport/index_en.txt.lzma";

    cpr::Response r = cpr::Get(cpr::Url{ url_index });
    std::cout << "Status code: " << r.status_code << '\n';

    std::ofstream indexLzma("json/indexLzma.txt.lzma", std::ios::out | std::ios::binary);
    if (indexLzma.is_open())
    {
        for (std::size_t i = 0; i < r.text.size(); ++i)
        {
            indexLzma.write((&r.text.c_str()[i]), sizeof(r.text.c_str()[i]));
        }
        indexLzma.close();
    }
    else std::cout << "Unable to open indexLzma";


    

    //------------------------------------------------------------------------------------------------------









	return 0;

}