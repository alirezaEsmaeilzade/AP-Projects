#include "Data_without_name.hpp"
Data_without_name::Data_without_name(){
    can_you_contain_anything = false;
}
Int_data_without_name::Int_data_without_name(int value){
    this->value = value;
}
void Int_data_without_name::print(int tab_number){
    print_tabs(tab_number);
    std::cout << value;
}
Str_data_without_name::Str_data_without_name(std::string value){
    this->value = value;
}
void Str_data_without_name::print(int tab_number){
    print_tabs(tab_number);
    std::cout << "\"" <<value << "\"";
}