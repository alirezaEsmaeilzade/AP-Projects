#ifndef __RESERVE_H__
#define __RESERVE_H__
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "date.hpp"
#include "room.hpp"
class Reserve{
    public:
        Reserve(std::string hotel_id, Date* date, double cost, std::vector<Room*> rooms, int id);
        bool your_id_is_this(int id);
        void print();
        double get_cansel_cost();
        void cansel_reserve();
        double get_cost();
        int get_room_number();
        double get_each_room_price();
    private:
        std::string hotel_id;
        Date* date;
        int id;
        double cost;
        std::vector<Room*> rooms;        
};
#endif
