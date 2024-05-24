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
#include <Windows.h>

#include <cpr/cpr.h>
#include "json.hpp"
#include <sciplot/sciplot.hpp>

using json = nlohmann::json;



//--------------------------------------------------------------------------------------------------------------------






//--------------------------------------------------------------------------------------------------------------------







int main()
{
    //------------------------------------------------------------------------------------------------------
	//API WARFRAME PUBLIC EXPORT
	//get version index

	std::string url_index = "https://origin.warframe.com/PublicExport/index_en.txt.lzma";

    cpr::Response r = cpr::Get(cpr::Url{ url_index },
        cpr::Authentication{ "user", "pass", cpr::AuthMode::BASIC },
        cpr::Parameters{ {"anon", "true"}, {"key", "value"} });
    std::cout << "Status code: " << r.status_code << '\n';
    std::cout << "Header:\n";
    for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
        std::cout << '\t' << kv.first << ':' << kv.second << '\n';
    }
    std::cout << "Text: " << r.text << '\n';

    //------------------------------------------------------------------------------------------------------












	return 0;

}