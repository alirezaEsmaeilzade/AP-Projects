#include "filter.hpp"
bool Filter_hotel::your_name_are_this(std::string filter_name){return this->filter_name == filter_name;}
Filter_by_city::Filter_by_city(std::string city) : Filter_hotel(){
    this->city = city;
    this->filter_name = "city";
}

std::vector<Hotel*> Filter_by_city::filter_hotel_datas(std::vector<Hotel*> hotels){
    std::vector<Hotel*> filterd_hotels;
    std::back_insert_iterator <std::vector< Hotel*> > back_it(filterd_hotels);
    std::string city = this->city;
    std::copy_if(hotels.begin(), hotels.end(), back_it, [=](Hotel* hotel){return hotel->your_city_are_this(city);});
    return filterd_hotels;
}

Filter_by_star_rating::Filter_by_star_rating(int max, int min) : Filter_hotel(){
    if(max > 5 || min < 1 || (min > max)){
        throw Run_time_error(BAD_REQUEST);
    }
    this->max_star = max;
    this->min_star = min;
    this->filter_name = "star";
}

std::vector<Hotel*> Filter_by_star_rating::filter_hotel_datas(std::vector<Hotel*> hotels){
    std::vector<Hotel*> filterd_hotels;
    std::back_insert_iterator <std::vector< Hotel*> > back_it(filterd_hotels);
    int min_star = this->min_star;
    int max_star = this->max_star;
    std::copy_if(hotels.begin(), hotels.end(), back_it, [=](Hotel* hotel){return (hotel->get_hotel_star() <= max_star) && (hotel->get_hotel_star() >= min_star);});
    return filterd_hotels;

}

Filter_by_price::Filter_by_price(double min_price, double max_price) : Filter_hotel(){
    if(min_price > max_price){
        throw Run_time_error(BAD_REQUEST);
    }
    this->min_price = min_price;
    this->max_price = max_price;
    this->filter_name = "price";
}
std::vector<Hotel*> Filter_by_price::filter_hotel_datas(std::vector<Hotel*> hotels){
    std::vector<Hotel*> filterd_hotels;
    std::back_insert_iterator <std::vector< Hotel*> > back_it(filterd_hotels);
    double min_price = this->min_price;
    double max_price =this->max_price;
    std::copy_if(hotels.begin(), hotels.end(), back_it, [=](Hotel* hotel){return (hotel->get_hotel_ave_price() <= max_price) && (hotel->get_hotel_ave_price() >= min_price);});
    return filterd_hotels;
}

Filter_type_room::Filter_type_room(std::string room_type, int quantity, Date* date) : Filter_hotel(){
    this->room_type = room_type;
    this->quantity = quantity;
    this->date = date;
    this->filter_name = "type";
}

std::vector<Hotel*> Filter_type_room::filter_hotel_datas(std::vector<Hotel*> hotels){
    std::vector<Hotel*> filterd_hotels;
    std::back_insert_iterator <std::vector< Hotel*> > back_it(filterd_hotels);
    std::string room_type = this->room_type;
    int quantity = this->quantity;
    Date* date = this->date;
    std::copy_if(hotels.begin(), hotels.end(), back_it, [=](Hotel* hotel){return hotel->check_have_special_room(room_type, quantity, date);});
    return filterd_hotels;        
}
Filter_defualt_budget::Filter_defualt_budget(User* user){
    this->user = user;
    this->filter_name = "default";
}

void Filter_defualt_budget::turn_off(){ activity = false;}
void Filter_defualt_budget::turn_on(){ activity = true;}
std::vector<Hotel*> Filter_defualt_budget::filter_hotel_datas(std::vector<Hotel*> hotels){
    std::vector<Hotel*> filterd_hotels;
    std::back_insert_iterator <std::vector< Hotel*> > back_it(filterd_hotels);
    double ave_price = user->return_ave();
    double standard_deviation = user->return_standard_deviation();
    std::copy_if(hotels.begin(), hotels.end(), back_it, [=](Hotel* hotel){ return std::abs(hotel->get_hotel_ave_price() - ave_price) <= 2 * standard_deviation;});
    std::cout << "* Results have been filtered by the default price filter." << std::endl;
    return filterd_hotels;
}
