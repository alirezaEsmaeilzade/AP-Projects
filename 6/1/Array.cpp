#include "Array.hpp"
Array::Array(int id) : Container(id){
    can_you_contain_int_or_str_datas = false;
}
void Array::add_string(std::string value){
    Str_data_without_name* new_data = new Str_data_without_name(value);
    elements.push_back(new_data);
}
void Array::add_int(int value){
    Int_data_without_name* new_data = new Int_data_without_name(value);
    elements.push_back(new_data);
}
Array_key::Array_key(std::string key, int id) : Array(id){
    this->key = key;
    have_got_name = true;
}
void Array_key::print(int tab_number){
    print_tabs(tab_number);
    if(tab_number != 0)
        std::cout << DUBBLE_COTTATION << key << DUBBLE_COTTATION <<": ";
    print_common_thing(ARRAY_SIGN_LEFT, ARRAY_SIGN_RIGHT,tab_number);
}
void Array_without_key::print(int tab_number){
    print_tabs(tab_number);
    print_common_thing(ARRAY_SIGN_LEFT, ARRAY_SIGN_RIGHT,tab_number);
}