#include "JsonBuilder.hpp"
JsonBuilder::JsonBuilder(){
    number_of_container = 0;
    mother_object = new Object_without_key(0);
}
JsonBuilder::~JsonBuilder(){
    mother_object->delete_member();
}
void JsonBuilder::addStringToObject(int parentId, std::string key, std::string value){
    if(parentId == 0){
        mother_object->add_str_data(key, value);
    }
    else{
        try{
            Container* find_dontainer = mother_object->search_container(parentId);
            if(find_dontainer == NULL || !find_dontainer->can_you_contain_int_and_str_data()){
                throw Run_time_error(ID_ERROR);
            }
            Object* find_object = (Object*)find_dontainer;
            find_object->add_str_data(key, value);
        }
        catch(Run_time_error error){
            std::cerr << error.what() << std::endl;
        }
    }
}
void JsonBuilder::addIntegerToObject(int parentId, std::string key, int value){
    if(parentId == 0){
        mother_object->add_int_data(key, value);
    }
    else{
        try{
            Container* find_container = mother_object->search_container(parentId);
            if(find_container == NULL || !find_container->can_you_contain_int_and_str_data()){
                    throw Run_time_error(ID_ERROR);
            }
            Object* find_object = (Object*)find_container;
            find_object->add_int_data(key, value);
        }
        catch(Run_time_error error){
            std::cerr << error.what() << std::endl;
        }
    }
}
void JsonBuilder::make_container_for_object(Container* object, std::string key, std::string type){
    number_of_container++;
    if(type == "object"){
        Object_key* new_data = new Object_key(key, number_of_container);
        object->add_container(new_data);
    }
    else if(type == "array"){
        Array_key* new_data = new Array_key(key, number_of_container);
        object->add_container(new_data);
    }
}
int JsonBuilder::addContainerToObject(int parentId, std::string key, std::string type){
    try{
        if(type != "object" && type != "array"){
            throw Run_time_error(TYPE_ERROR);
        }
        if(parentId == 0){
            if(mother_object->check_duplicated_key(key)){
                throw Run_time_error(KEY_ERROR);
            }
            make_container_for_object(mother_object, key, type);
        }
        else{
            Container* find_container = mother_object->search_container(parentId);
            if(find_container->check_duplicated_key(key)){
                throw Run_time_error(KEY_ERROR);
            }
            if(find_container == NULL || !find_container->can_you_contain_int_and_str_data()){
                throw Run_time_error(ID_ERROR);
            }
            make_container_for_object(find_container, key, type);
        }
        return number_of_container;    
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
        return -1;
    }
}
void JsonBuilder::addStringToArray(int parentId, std::string value){
    try{
        Container* find_container = mother_object->search_container(parentId);
        if(find_container == NULL || find_container->can_you_contain_int_and_str_data()){
            throw Run_time_error(ID_ERROR);
        }
        Array* find_array = (Array*)find_container;
        find_array->add_string(value);
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}
void JsonBuilder::addIntegerToArray(int parentId, int value){
    try{
        Container* find_container = mother_object->search_container(parentId);
        if(find_container == NULL || find_container->can_you_contain_int_and_str_data()){
            throw Run_time_error(ID_ERROR);
        }
        Array* find_array = (Array*)find_container;
        find_array->add_int(value);
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}
int JsonBuilder::addContainerToArray(int parentId, std::string type){
    try{
        if(type != "object" && type != "array"){
            throw Run_time_error(TYPE_ERROR);
        }
        Container* find_container = mother_object->search_container(parentId);
        if(find_container == NULL || find_container->can_you_contain_int_and_str_data()){
            throw Run_time_error(ID_ERROR);
        }
        number_of_container++;
        if(type == "object"){
            Object_without_key* new_object = new Object_without_key(number_of_container);
            find_container->add_container(new_object);
        }
        else if(type == "array"){
            Array_without_key* new_array = new Array_without_key(number_of_container);
            find_container->add_container(new_array);
        }
        return number_of_container;
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
        return -1;
    }
}
void JsonBuilder::print(int id){
    try{
        if(id == 0){
            mother_object->print(0);
        }
        else{
            Container* find = mother_object->search_container(id);
            if(find == NULL || !find->can_you_contain_int_and_str_data()){
                throw Run_time_error(ID_ERROR);
            }
            find->print(0);
        }
        std::cout << "\n";
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}