#ifndef __HOTEL_H__
#define __HOTEL_H__
#include <string>
#include <vector>
#include "comment.hpp"
#include "room.hpp"
#include "rating.hpp"
#include "functions.hpp"
#include "user.hpp"
#include "error.hpp"
#define COMMA ','
#define CHARACTER '|'
#define SETPRECISION_NUMBER 2
class Hotel{
    public:
        Hotel(std::vector <std::string> inputs);
        ~Hotel();
        void print();
        void print_hotel_some_data();
        void add_comment(User* user, std::string comment);
        void add_rate(User* user ,Rating* rating);
        void print_hotel_comment();
        void print_hotel_rate();
        bool Hotels_id_is_this(std::string id);
        bool your_city_are_this(std::string city);
        int get_hotel_star();
        double get_hotel_ave_price();
        double calcute_rooms_price(std::string type_room, int quantity, int check_in, int check_out);
        bool check_have_special_room(std::string type_room, int quantity, Date* date);
        std::vector<Room*> return_reserve_room(std::string type_room, int quantity, Date* new_date);
        std::vector<Room*> return_special_room(std::string type_room, int quantity, Date* new_date);
        std::string get_id();
        std::string get_name();
        std::string get_city();
        double get_standard_price();
        double get_delux_price();
        double get_luxury_price();
        double get_premium_price();
        void initialize_rating(std::vector<std::string> datas);
        double hotel_ave_rate(User* logined_user);
    private:
        template <typename T>
        void initialize_room(int number, int price);
        double initialize_average();
        void print_property_anemities();
        std::vector<double> calcute_all_rate();
        void delete_duplicated_rate(User* user);
        std::string unique_id;
        std::string property_name;
        int hotel_star_rating;
        std::string hotel_overview;
        std::vector <std::string> property_amenities;
        std::string city;
        double latitude;
        double longitude;
        std::string image_url;
        int num_of_standard_rooms;
        int num_of_deluxe_rooms;
        int num_of_luxury_rooms;
        int num_of_premium_rooms;
        int standard_room_price;
        int deluxe_room_price;
        int luxury_room_price;
        int premium_room_price;
        double price_average;
        int room_number;
        std::vector <Comment*> comments;
        std::vector<Room*> rooms;
        std::vector<Rating*> ratings;
        Read_rating* read_rating;
};
#endif