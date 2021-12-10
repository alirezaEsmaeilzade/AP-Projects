#ifndef __DATA_WITH_NAME_H__
#define __DATA_WITH_NAME_H__
#include "Element.hpp"
#include <iostream>
#include <string>

class Data_with_name : public Element{
    public:
        Data_with_name(std::string name);
        virtual bool your_key_is_this(std::string key) = 0;
        virtual void print(int tab_number) = 0;
    protected:
        std::string name;
};
class Int_data_with_name : public Data_with_name{
    public:
        Int_data_with_name(std::string name, int amount);
        virtual bool your_key_is_this(std::string key){return name == key;}
        virtual void print(int tab_number);
    private:
        int amount;
};
class String_data_with_name : public Data_with_name{
    public:
        String_data_with_name(std::string name, std::string amount);
        virtual bool your_key_is_this(std::string key){return name == key;}
        virtual void print(int tab_number);
    private:
        std::string amount;
};
#endif