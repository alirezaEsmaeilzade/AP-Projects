#ifndef __ELEMENT_H__
#define __ELEMENT_H__
#include <iostream>
#define ARRAY_SIGN_LEFT '['
#define ARRAY_SIGN_RIGHT ']'
#define OBJECT_SIGN_LEFT '{'
#define OBJECT_SIGN_RIGHT '}'
#define DUBBLE_COTTATION '"'
#define COMMA ','
#define TAB "    "
void print_tabs(int tab_number);
class Element{
    public:
        bool can_you_contian(){return can_you_contain_anything;}
        virtual void print(int tab_number) = 0;
        virtual bool your_key_is_this(std::string key) = 0;
    protected:
        bool can_you_contain_anything;
};
#endif