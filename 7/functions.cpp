#include "functions.hpp"
std::vector<std::string> split_string(std::string unsplit, char separator){
    std::vector<std::string> splited_string_part;
    std::stringstream ss(unsplit);
    while(ss.good()){
        std::string substr;
        getline(ss, substr, separator);
        if(substr[0] == ' ')
            substr.erase(substr.begin());
        if(!substr.empty())
            splited_string_part.push_back(substr);
    }
    return splited_string_part;
}

bool is_integer(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_positive_float(const std::string& s){
    std::string::const_iterator it = s.begin();
    int comma_count = 0;
    while (it != s.end() && comma_count <= 1 && (std::isdigit(*it) || *it == '.')){ 
        if(*it == '.')
            comma_count++;
        ++it;
    }
    return !s.empty() && it == s.end() && (s.front() != '.') && (s.back() != '.');
}

