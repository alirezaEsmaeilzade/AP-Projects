#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "Container.hpp"
#include "Data_with_name.hpp"
#include <iostream>

class Object : public Container{
    public:
        Object(int id);
        void add_str_data(std::string key, std::string value);
        void add_int_data(std::string key, int value);
        virtual bool your_key_is_this(std::string key) = 0;
        virtual void print(int tab_number) = 0;
};
class Object_without_key : public Object{
    public:
        Object_without_key(int id) : Object(id){
            have_got_name = false;
        }
        virtual bool your_key_is_this(std::string key){return false;}
        virtual void print(int tab_number);
};
class Object_key : public Object{
    public:
        Object_key(std::string key, int id) : Object(id){
            this->key = key;
            have_got_name = true;
        }
        virtual bool your_key_is_this(std::string key){return this->key == key;}
        virtual void print(int tab_number);
    private:
        std::string key;
};
#endif