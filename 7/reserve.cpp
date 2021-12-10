#include "reserve.hpp"
Reserve::Reserve(std::string hotel_id, Date* date, double cost, std::vector<Room*> rooms, int id){
    this->hotel_id = hotel_id;
    this->date = date;
    this->cost = cost;
    this->rooms = rooms;
    this->id = id;
}

bool Reserve::your_id_is_this(int id){return this->id == id;}
void Reserve::print(){
    std::cout << "id: " << id << ' ';
    std::cout << "hotel: " << hotel_id << ' ';
    rooms[0]->print_type();
    std::cout << "quantity: " << rooms.size() << ' ';
    std::cout << "cost: " << (int)cost << ' ' << "check_in " << date->get_start() << ' ';
    std::cout << "check_out " << date->get_end();
}

double Reserve::get_cansel_cost(){return cost / 2;}//////int havaset bashe
void Reserve::cansel_reserve(){
    for(int i = 0; i < rooms.size(); i++){
        rooms[i]->cansel(date);
    }
}
double Reserve::get_cost(){ 
    if(rooms.size() == 0)
        return 0;
    else
        return rooms[0]->get_price() * rooms.size();
}
int Reserve::get_room_number(){ return rooms.size();}
double Reserve::get_each_room_price(){
    if(rooms.size() == 0)
        return 0;
    else
        return rooms[0]->get_price();
}
