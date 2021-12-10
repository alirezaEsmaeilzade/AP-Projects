#include "functions.h"
void print_string_vector(std::vector< std::string> input){
    for(int i = 0; i < input.size(); i++){
        std::cout<< input[i];
        if(input.size() - 1 != i)
            std::cout<< ", ";
    }
    std::cout << std::endl;
}
void print_sorted_string_vector(std::vector< std::string> input){
    std::vector<std::string> sorted_input = input;
    sort(sorted_input.begin(), sorted_input.end());
    print_string_vector(sorted_input);
}
std::vector<std::string> split_string(std::string unsplit, char separator){
    std::vector<std::string> splited_string_part;
    std::stringstream ss(unsplit);
    while(ss.good()){
        std::string substr;
        getline(ss, substr, separator);
        if(substr[0] == ' ')
            substr.erase(substr.begin());
        splited_string_part.push_back(substr);
    }
    return splited_string_part;
}
