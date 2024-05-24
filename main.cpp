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
	std::ifstream parameterJsonStream("json/parametre.json");
	json parameterJson = json::parse(parameterJsonStream);



	std::cout << parameterJson << std::endl;

	//---------------------------------------------------------------------------------

	cpr::Response r = cpr::Get(cpr::Url{ "https://api.github.com/repos/whoshuu/cpr/contributors" },
		cpr::Authentication{ "user", "pass", cpr::AuthMode::BASIC },
		cpr::Parameters{ {"anon", "true"}, {"key", "value"} });
	std::cout << "Status code: " << r.status_code << '\n';
	std::cout << "Header:\n";
	for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
		std::cout << '\t' << kv.first << ':' << kv.second << '\n';
	}
	std::cout << "Text: " << r.text << '\n';



	//---------------------------------------------------------------------------------


    // Create a vector with values from 0 to pi divived into 200 uniform intervals for the x-axis
    sciplot::Vec x = sciplot::linspace(0.0, sciplot::PI, 200);

    // Create a Plot object
    sciplot::Plot2D plot;

    // Set the x and y labels
    plot.xlabel("x");
    plot.ylabel("y");

    // Set the x and y ranges
    plot.xrange(0.0, sciplot::PI);
    plot.yrange(0.0, 1.0);

    // Set the legend to be on the bottom along the horizontal
    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);

    // Plot sin(i*x) from i = 1 to i = 6
    plot.drawCurve(x, std::sin(1.0 * x)).label("sin(x)");
    plot.drawCurve(x, std::sin(2.0 * x)).label("sin(2x)");
    plot.drawCurve(x, std::sin(3.0 * x)).label("sin(3x)");
    plot.drawCurve(x, std::sin(4.0 * x)).label("sin(4x)");
    plot.drawCurve(x, std::sin(5.0 * x)).label("sin(5x)");
    plot.drawCurve(x, std::sin(6.0 * x)).label("sin(6x)");

    // Create figure to hold plot
    sciplot::Figure fig = { {plot} };
    // Create canvas to hold figure
    sciplot::Canvas canvas = { {fig} };

    // Show the plot in a pop-up window
    canvas.show();

    // Save the plot to a PDF file
    canvas.save("example-sine-functions.pdf");

	return 0;

}