#ifndef __FILTER_H__
#define __FILTER_H__
#include "hotel.hpp"
#include "date.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
class Filter_hotel{
    public:
        Filter_hotel(){}
        virtual std::vector<Hotel*> filter_hotel_datas(std::vector<Hotel*> hotels) = 0;
        bool your_name_are_this(std::string filter_name);
    protected:
        std::string filter_name;
};
class Filter_by_city : public Filter_hotel{
    public:
        Filter_by_city(std::string city);
        virtual std::vector<Hotel*> filter_hotel_datas(std::vector<Hotel*> hotels);
    private:
        std::string city;
};
class Filter_by_star_rating : public Filter_hotel{
    public:
        Filter_by_star_rating(int max, int min);
        virtual std::vector<Hotel*> filter_hotel_datas(std::vector<Hotel*> hotels);
    private:
        int max_star;
        int min_star;
};
class Filter_by_price : public Filter_hotel{
    public:
        Filter_by_price(double min_price, double max_price);
        virtual std::vector<Hotel*> filter_hotel_datas(std::vector<Hotel*> hotels);
    private:
        double min_price;
        double max_price;
};
class Filter_type_room : public Filter_hotel{
    public:
        Filter_type_room(std::string room_type, int quantity, Date* date);
        virtual std::vector<Hotel*> filter_hotel_datas(std::vector<Hotel*> hotels);
    private:
        Date* date;
        std::string room_type;
        int quantity;
};
class Filter_defualt_budget : public Filter_hotel{
    public:
        Filter_defualt_budget(User* user);
        virtual std::vector<Hotel*> filter_hotel_datas(std::vector<Hotel*> hotels);
        void turn_off();
        void turn_on();
    private:
        double return_price_ave(std::vector<Hotel*> hotels);
        double calcute_standard_deviation(std::vector<Hotel*> hotels);
        bool activity;
        double standard_deviation;
        User* user;
};
#endif