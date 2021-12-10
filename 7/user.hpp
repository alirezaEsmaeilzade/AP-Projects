#ifndef __USER_H__
#define __USER_H__
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "error.hpp"
#include "reserve.hpp"
#include "manual_weight.hpp"
#define EPSILON 0.0001
class Rating;
class User{
    public:
        User(std::string username, std::string password, std::string email);
        ~User();
        bool your_password_is_this(std::string password);
        bool your_email_is_this(std::string email);
        void print_username_for_comment();
        void pay_hotel_cast(double cast);
        bool your_username_is_this(std::string username);
        void add_amount_to_wallet(double amount);
        void get_transaction(int count);
        void submit_reserve(std::string hotel_id, std::vector<Room*> rooms, Date* reserve_date);
        void print_reserves_info();
        Reserve* find_reserve(int id);
        void delete_reserve(int id);
        double return_ave();
        double return_standard_deviation();
        int get_reserves_num();
        void set_manual_weight(std::string acctivity_conditoin, double location_w, double cleanliness_w, double staff_w, double facilities_w, double value_for_money_w);
        void set_manual_weight_inactive(std::string acctivity_conditoin);
        double calcut_manual_weight(std::vector<double> rates);
        void add_rate(Rating* new_rate);
        void delete_duplicated_rate(Rating* duplicate);
        void print_manual_weights();
        bool manual_weight_activity();
        bool is_estimated_condition_ok();
        void estimate_weights();
        void print_estimated_weights();
    private:
        double calcute_room_price(std::vector<Room*> rooms, Date* date);
        void delete_reserve_from_vector(Reserve* for_delete);
        unsigned long int generate_password_hash(std::string  password);
        double f(std::vector<double> x, std::vector<double> w);
        double E(std::vector<double> x, std::vector<double> w, double y);
        double E_partial_derivative(std::vector<double> x, std::vector<double> w, int index, double y);
        std::string username;
        unsigned long int password;
        std::string email;
        double amount;
        std::vector<double> transaction;
        std::vector<Reserve*> reserves;
        Manual_weights weights;
        std::vector<Rating*> ratings;
        bool estimated_weight;
};
#endif