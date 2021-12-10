#ifndef __RATING_H__
#define __RATING_H__
#include <iomanip>
#include <iostream>
#include <map>
#include <algorithm>
#include "error.hpp"
#include "user.hpp"
#define SETPRECISION_NUMBER 2
typedef std::vector< std::pair <std::string, double> > element;
class Rating{
    public:
        Rating(User* user, double location, double cleanliness, double staff, double facilities, double value_for_money, double overall_rating);
        bool check_user(User* user);
        double get_location();
        double get_cleanliness();
        double get_staff(); 
        double get_facilities();
        double get_value_for_money();
        double get_overall_rating();
        std::vector<double> get_rating();
    private:
        bool check_number(double input_rate);
        User* user;
        element elements;

};
class Read_rating{
    public:
        Read_rating(std::vector<std::string> input);
        void print();
        double get_overall_rating();
        std::vector<double> get_rates();
    private:
        element elements;
};
#endif