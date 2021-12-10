#include "Object.hpp"
Object::Object(int id) : Container(id){
    can_you_contain_int_or_str_datas = true;
}
void Object::add_str_data(std::string key, std::string value){
    String_data_with_name* new_data = new String_data_with_name(key, value);
    elements.push_back(new_data);
}
void Object::add_int_data(std::string key, int value){
    Int_data_with_name* new_data = new Int_data_with_name(key, value);
    elements.push_back(new_data);
}
void Object_without_key::print(int tab_number){
    print_tabs(tab_number);
    print_common_thing(OBJECT_SIGN_LEFT, OBJECT_SIGN_RIGHT, tab_number);
}
void Object_key::print(int tab_number){
    print_tabs(tab_number);
    if(tab_number != 0)
        std::cout<< DUBBLE_COTTATION << key << DUBBLE_COTTATION << ": ";
    print_common_thing(OBJECT_SIGN_LEFT, OBJECT_SIGN_RIGHT, tab_number);
}