#include "Data_with_name.hpp"
Data_with_name::Data_with_name(std::string name){
    this->name = name;
    can_you_contain_anything = false;
}
Int_data_with_name::Int_data_with_name(std::string name, int amount) : Data_with_name(name){
    this->amount = amount;
}
void Int_data_with_name::print(int tab_number){
    print_tabs(tab_number);
    std::cout<< DUBBLE_COTTATION << name << "\": " << amount;
}
String_data_with_name::String_data_with_name(std::string name, std::string amount) : Data_with_name(name){
    this->amount = amount;
}
void String_data_with_name::print(int tab_number){
    print_tabs(tab_number);
    std::cout<< DUBBLE_COTTATION << name << "\": "<< DUBBLE_COTTATION << amount << DUBBLE_COTTATION;
}