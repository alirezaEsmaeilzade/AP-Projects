#ifndef _AUTHOR_H_
#define _AUTHOR_H_
#include "functions.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#define separator_one ','
#define separator_two '$'

class Author{
    public:
        void initialize(std::string inputs);
        Author(std::string input){
            initialize(input);
        }
        bool is_id_correct(int id);
        std::string get_name(){return name;}
        int get_id(){return id;}
        void print();
    private:
        int id;
        std::string name;
        std::string gender;
        std::string member_since;
        int year_of_birth;
        std::string place_of_birth;
        std::vector<std::string> genres;
};
#endif