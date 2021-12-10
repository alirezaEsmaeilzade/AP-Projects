#ifndef __ARRAY_H__
#define __ARRAY_H__
#include "Container.hpp"
#include "Data_without_name.hpp"
#include <iostream>

class Array : public Container{
    public:
        Array(int id);
        virtual void print(int tab_number) = 0;
        virtual bool your_key_is_this(std::string key) = 0;
        void add_string(std::string value);
        void add_int(int value);
};
class Array_key : public Array{
    public:
        Array_key(std::string key, int id);
        virtual bool your_key_is_this(std::string key){return this->key == key;}
        virtual void print(int tab_number);
    private:
        std::string key;
};
class Array_without_key : public Array{
    public:
        Array_without_key(int id) : Array(id){
            have_got_name = false;
        }
        virtual bool your_key_is_this(std::string key){return false;}
        virtual void print(int tab_number);
};
#endif