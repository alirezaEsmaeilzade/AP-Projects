#ifndef __CONTAINER_H__
#define __CONTAINER_H__
#include "Element.hpp"
#include <vector>
class Container : public Element{
    public:
        Container(int id);
        virtual void print(int tab_number) = 0;
        bool your_id_is_this(int id){return this->id == id;}
        bool can_you_contain_int_and_str_data(){return can_you_contain_int_or_str_datas;}
        Container* search_container(int parentID);
        void add_container(Element* new_data);
        virtual bool your_key_is_this(std::string key) = 0;
        bool check_duplicated_key(std::string key);
        void delete_member();
        void print_common_thing(char start_char, char end_char, int tab_number);
    protected:
        int id;
        bool can_you_contain_int_or_str_datas;
        bool have_got_name;
        std::vector <Element*> elements;
};
#endif