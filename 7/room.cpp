#include "room.hpp"
Room::Room(int price){
    this->price = price;
}

Room::~Room(){
    std::for_each(reserved_day.begin(), reserved_day.end(), [](Date* date){delete date;});
    reserved_day.clear();
}

bool Room::your_type_is_this(std::string type){return room_type == type;}
int Room::get_price(){return price;}
void Room::reserve(Date* reserve_day){ reserved_day.push_back(reserve_day);}
void Room::print_id(){std::cout << id;}
void Room::print_type(){std::cout << "room: " << room_type << ' ';}
void Room::cansel(Date* cansel_date){
    for(int i = 0; i < reserved_day.size(); i++){
        if(!reserved_day[i]->check_interference(cansel_date)){
            delete reserved_day[i];
            reserved_day.erase(reserved_day.begin() + i);
        }
    }
}

bool Room::are_you_can_reserve_in_this_date(Date* check){
    return !std::any_of(reserved_day.begin(), reserved_day.end(), [=](Date* date){return !date->check_interference(check);});
}

Standard_room::Standard_room(std::string id, int price) : Room(price){
    this->id = STANDARD_ROOM_NAME + id;
    room_type = STANDARD_ROOM_TYPE;
}

Delux_room::Delux_room(std::string id, int price) : Room(price){
    this->id = DELUX_ROOM_NAME + id;
    room_type = DELUXE_ROOM_TYPE;
}

Luxury_room::Luxury_room(std::string id, int price) : Room(price){
    this->id = LUXURY_ROOM_NAME + id;
    room_type = LUXURY_ROOM_TYPE;
}

Premium_room::Premium_room(std::string id, int price) : Room(price){
    this->id = PREMIUM_ROOM_NAME + id;
    room_type = PREMIUM_ROOM_TYPE;
}