#include "usefullFunction.hpp"

std::string clean_string_symbols(std::string str)
{
    std::string c_str = str;

    while (c_str.find("\r") != std::string::npos)
    {
        c_str.replace(c_str.find("\r"), 2, "");
    }
    while (c_str.find("\"") != std::string::npos)
    {
        c_str.replace(c_str.find("\""), 1, "");
    }
    while (c_str.find("<") != std::string::npos)
    {
        c_str.replace(c_str.find("<"), 1, "");
    }
    while (c_str.find(">") != std::string::npos)
    {
        c_str.replace(c_str.find(">"), 1, "");
    }

    return c_str;
}

std::string cleanRetourChariot(std::string fichier)
{
    fichier.erase(std::remove(fichier.begin(), fichier.end(), '\r'), fichier.end());
    return fichier;
}

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}


std::vector<std::string> pop_front(std::vector<std::string> vec)
{
    vec.erase(vec.begin());
    return vec;
}