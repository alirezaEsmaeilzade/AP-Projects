#ifndef __ROOM_H__
#define __ROOM_H__
#include "date.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#define PREMIUM_ROOM_NAME "p"
#define DELUX_ROOM_NAME "d"
#define STANDARD_ROOM_NAME "s"
#define LUXURY_ROOM_NAME "l"
#define PREMIUM_ROOM_TYPE "premium"
#define DELUXE_ROOM_TYPE "deluxe"
#define STANDARD_ROOM_TYPE "standard"
#define LUXURY_ROOM_TYPE "luxury"

class Room{
    public:
        Room(int price);
        ~Room();
        bool are_you_can_reserve_in_this_date(Date* need_date);
        bool your_type_is_this(std::string type);
        int get_price();
        void reserve(Date* reserve_day);
        void print_id();
        void print_type();
        void cansel(Date* cansel_date);
    protected:
        std::string id;
        int price;
        std::string room_type;
        std::vector <Date*> reserved_day;
};
class Standard_room : public Room{
    public:
        Standard_room(std::string id, int price);
};

class Delux_room : public Room{
    public:
        Delux_room(std::string id, int price);
};
class Luxury_room : public Room{
    public:
        Luxury_room(std::string id, int price);
};
class Premium_room : public Room{
    public:
        Premium_room(std::string id, int price);
};

#endif
