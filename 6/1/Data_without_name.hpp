#ifndef __DATA_WITHOUT_NAME_H__
#define __DATA_WITHOUT_NAME_H__
#include "Element.hpp"
#include <iostream>
#include <string>

class Data_without_name : public Element{
    public:
        Data_without_name();
        virtual bool your_key_is_this(std::string key) = 0;
        virtual void print(int tab_number) = 0;
};
class Int_data_without_name : public Data_without_name{
    public:
        Int_data_without_name(int value);
        virtual bool your_key_is_this(std::string key){ return false;}
        virtual void print(int tab_number);
    private:
        int value;
};
class Str_data_without_name : public Data_without_name{
    public:
        Str_data_without_name(std::string value);
        virtual bool your_key_is_this(std::string key){ return false;}
        virtual void print(int tab_number);
    private:
        std::string value;
};
#endif