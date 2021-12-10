#include "Container.hpp"
Container::Container(int id){
    this->id = id;
    can_you_contain_anything = true;
}
Container* Container::search_container(int parentID){
    for(int i = 0; i < elements.size(); i++){
        if(elements[i]->can_you_contian()){
            Container* container = (Container*)elements[i];
            if(container->your_id_is_this(parentID)){
                return container;
            }
            Container* find_container = container->search_container(parentID);
            if(find_container != NULL){
                return find_container;
            }
        }
    }
    return NULL;
}
bool Container::check_duplicated_key(std::string key){
    if(your_key_is_this(key))
        return true;
    for(int i = 0; i < elements.size(); i++){
        if(elements[i]->your_key_is_this(key))
            return true;
    }
    return false;
}
void Container::add_container(Element* new_data){
    elements.push_back(new_data);
}
void Container::delete_member(){
    for(int i = 0; i < elements.size(); i++){
        if(elements[i]->can_you_contian()){
            Container* for_delet = (Container*) elements[i];
            for_delet->delete_member();
            delete elements[i];
        }
        else
            delete elements[i];
        
    }
}
void Container::print_common_thing(char start_char, char end_char, int tab_number){
    std::cout << start_char;
    if(!elements.empty())
        std::cout<< std::endl;
    for(int i = 0; i < elements.size(); i++){
        elements[i]->print(tab_number + 1);
        if(i + 1 != elements.size())
            std::cout<< COMMA;
        std::cout<< std::endl;
    }
    if(!elements.empty())
        print_tabs(tab_number);
    std::cout<< end_char;
}