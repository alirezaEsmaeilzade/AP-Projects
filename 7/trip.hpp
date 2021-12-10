#ifndef __TRIP_H__
#define __TRIP_H__
#include "user.hpp"
#include "filter.hpp"
#include "hotel.hpp"
#include "error.hpp"
#include "date.hpp"
#include "sort.hpp"
#include "functions.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#define COMMA ','
#define CHARACTER '|'
#define BAD_REQUEST "Bad Request"
#define LOGINE_ERROR "Permission Denied"
#define EMPTY_DATA "Empty"
#define FOUND_ERROR "Not Found"
#define MISSION_ACCOMPLISHED_MASSAGE "OK"

bool comapre(Hotel* one, Hotel* two);
class Trip{
    public:
        Trip(std::string hotels_file_name, std::string ratings_file_name);
        ~Trip();
        void logout();
        void add_new_user(std::string username, std::string password, std::string email);
        void login_user(std::string username, std::string password);
        void print_all_hotel();
        void print_hotel_by_id(std::string id);
        void add_city_filter(std::string filter_type);
        void add_star_filter(int min_star, int max_star);
        void add_price_filter(double min_price, double max_price);
        void add_type_filter(std::string room_type, int quantity, int check_in, int check_out);
        void delete_filter();
        void add_comment(std::string hotel_id, std::string comment);
        void get_hotel_comment(std::string hotel_id);
        void add_rate(std::string hotel_id, double location, double cleanliness, double staff, double facilities, double value_for_money, double overall_rating);
        void get_hotel_rate(std::string hotel_id);
        void add_amount_to_user_wallet(double amount);
        void get_user_transaction(int count);
        void reserve_room(std::string hotel_id, std::string type_room, int quantity, int check_in, int check_out);
        void see_reserves();
        void cansel_reserve(int id);
        void change_hotel_sort(std::string sort_type, std::string command);
        void change_default_filter(std::string condition);
        void save_manual_weights(std::string active_condition, double location_w, double cleanliness_w, double staff_w, double facilities_w, double value_for_money_w);
        void inactive_manual_weights(std::string active_condition);
        void get_manual_weights();
        void get_estimated_weights();
    private:
        void check_defualt_filter();
        bool check_city_is_exist(std::string city);
        bool check_user_dupplicat(std::string user_name, std::string email);
        User* find_user(std::string username, std::string password);
        void read_data_from_file(std::string file_name);
        void read_rating_datas_from_file(std::string file_name);
        Hotel* find_hotel(std::string id);
        void print_room_name(std::vector<Room*> rooms);
        void change_dupplicated_filter(std::string filter_name);
        void print_accomplished();
        std::vector<Hotel*> filter_result();
        std::vector <Hotel*> hotels; 
        std::vector< User*> users;
        User* logined_user;
        std::vector<Filter_hotel*> filters;
        bool defualt_filter_activity;
        Sort sort;
};
#endif
