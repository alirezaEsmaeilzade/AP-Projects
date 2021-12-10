#include "trip.hpp"
Trip::Trip(std::string hotels_file_name, std::string ratings_file_name){
    read_data_from_file(hotels_file_name);
    read_rating_datas_from_file(ratings_file_name);
    logined_user = NULL;
}
Trip::~Trip(){
    std::for_each(hotels.begin(), hotels.end(), [](Hotel* hotel){delete hotel;});
    hotels.clear();
    std::for_each(users.begin(), users.end(), [](User* user){delete user;});
    users.clear();
    std::for_each(filters.begin(), filters.end(), [](Filter_hotel* filter){delete filter;});
    filters.clear();
}
void Trip::print_accomplished(){
    std::cout << MISSION_ACCOMPLISHED_MASSAGE << std::endl;
}
void Trip::read_data_from_file(std::string file_name){
    std::ifstream datas;
    datas.open(file_name);
    if(!datas.is_open())
        throw Run_time_error("file is not exits!");
    std::string head_of_table;
    std::string a_line_of_file;
    std::getline(datas, a_line_of_file);
    while (!datas.eof()){
        std::getline(datas, a_line_of_file, '\n');
        if(!a_line_of_file.empty()){
            Hotel* hotel = new Hotel(split_string(a_line_of_file, COMMA));
            hotels.push_back(hotel);
        }
    }
}
void Trip::read_rating_datas_from_file(std::string file_name){
    std::ifstream datas;
    datas.open(file_name);
    if(!datas.is_open())
        throw Run_time_error("file is not exits!");
    std::string head_of_table;
    std::string a_line_of_file;
    std::getline(datas, a_line_of_file);
    while (!datas.eof()){
        std::getline(datas, a_line_of_file, '\n');
        if(!a_line_of_file.empty()){
            std::vector <std::string> line_of_file = split_string(a_line_of_file, COMMA);
            std::string hotel_id = line_of_file.front();
            line_of_file.erase(line_of_file.begin());
            auto it = std::find_if(hotels.begin(), hotels.end(), [hotel_id](Hotel* hotel){return hotel->Hotels_id_is_this(hotel_id);});
            (*it)->initialize_rating(line_of_file);
        }
    }
}

bool Trip::check_user_dupplicat(std::string username, std::string email){
    return !std::any_of(users.begin(), users.end(), [=](User* user){return user->your_username_is_this(username) || user->your_email_is_this(email);});
}
User* Trip::find_user(std::string username, std::string password){
    auto user_it = std::find_if(users.begin(), users.end(), [=](User* user){return user->your_username_is_this(username) && user->your_password_is_this(password);});
    if(user_it != users.end())
        return *user_it;
    return NULL;
}
void Trip::add_new_user(std::string username, std::string password, std::string email){
    if(!check_user_dupplicat(username, email))
        throw Bad_request();
    User* new_user = new User(username, password, email);
    users.push_back(new_user);
    logined_user = new_user;
    defualt_filter_activity = true;
    print_accomplished();
}

void Trip::login_user(std::string username, std::string password){
    if(logined_user != NULL)
        throw Bad_request();
    User* finded_user = find_user(username, password);
    if(finded_user == NULL)
        throw Bad_request();
    logined_user = finded_user;
    defualt_filter_activity = true;
    print_accomplished();
}
void Trip::logout(){
    if(logined_user == NULL)
        throw Bad_request();
    logined_user = NULL;
    delete_filter();
}
Hotel* Trip::find_hotel(std::string id){
    auto hotel_it = std::find_if(hotels.begin(), hotels.end(), [=](Hotel* hotel){return hotel->Hotels_id_is_this(id);});
    if(hotel_it != hotels.end())
        return *hotel_it;
    return NULL;
}
bool Trip::check_city_is_exist(std::string city){
    return std::any_of(hotels.begin(), hotels.end(), [=](Hotel* hotel){return hotel->your_city_are_this(city);});
}
void Trip::change_dupplicated_filter(std::string filter_name){
    for(int i = 0; i < filters.size(); i++){
        if(filters[i]->your_name_are_this(filter_name)){
            delete filters[i];
            filters.erase(filters.begin() + i);
        }
    }
}
void Trip::add_city_filter(std::string city){
    if(!check_city_is_exist(city)){
        throw Bad_request();
    }
    Filter_by_city* new_filter = new Filter_by_city(city);
    change_dupplicated_filter("city");
    filters.push_back(new_filter);
    print_accomplished();
        
}
void Trip::add_star_filter(int min_star, int max_star){
    Filter_by_star_rating* new_filter = new Filter_by_star_rating(max_star, min_star);
    change_dupplicated_filter("star");
    filters.push_back(new_filter);
    print_accomplished();

}
void Trip::add_price_filter(double min_price, double max_price){
    Filter_by_price* new_filter = new Filter_by_price(min_price, max_price);
    change_dupplicated_filter("price");
    filters.push_back(new_filter);
    defualt_filter_activity = false;
    print_accomplished();
    
}
void Trip::add_type_filter(std::string room_type, int quantity, int check_in, int check_out){
    Date* date = new Date(check_in, check_out);
    Filter_type_room* new_filter = new Filter_type_room(room_type, quantity, date);
    change_dupplicated_filter("type");
    filters.push_back(new_filter);
    print_accomplished();
}
void Trip::check_defualt_filter(){
    bool default_filter_exist = std::any_of(filters.begin(), filters.end(), [](Filter_hotel* filter){return filter->your_name_are_this("default");});
    if(logined_user->get_reserves_num() >= 10 && defualt_filter_activity && !default_filter_exist){
        Filter_defualt_budget* new_filter = new Filter_defualt_budget(logined_user);
        filters.push_back(new_filter);
    }
    else{
        if(default_filter_exist){
            std::vector<Filter_hotel*>::iterator it;
            it = std::find_if(filters.begin(), filters.end(), [](Filter_hotel* filter){return filter->your_name_are_this("default");});
            delete *it;
            filters.erase(it);
        }
    }
}
void Trip::change_default_filter(std::string condition){
    if(condition == "true")
        defualt_filter_activity = true;
    else if(condition == "false"){
        change_dupplicated_filter("default");
        defualt_filter_activity = false;
    }
    else
        throw Bad_request();
}

void Trip::delete_filter(){
    std::for_each(filters.begin(), filters.end(), [](Filter_hotel* filter){delete filter;});
    filters.clear();
    print_accomplished();
}

std::vector<Hotel*> Trip::filter_result(){
    std::vector<Hotel*> filtered_result = hotels;
    check_defualt_filter();
    for(int i = 0; i < filters.size(); i++)
        filtered_result = filters[i]->filter_hotel_datas(filtered_result);
    return filtered_result;
}

void Trip::print_all_hotel(){
    if(logined_user == NULL)
        throw Login_error();
    if(hotels.size() == 0)
        throw Empty_data_error();
    std::vector<Hotel*> filtered_result = filter_result();
    std::vector<Hotel*> sorted = sort.sort(filtered_result, logined_user);
    std::for_each(sorted.begin(), sorted.end(), [](Hotel* hotel){hotel->print_hotel_some_data();});
}

void Trip::print_hotel_by_id(std::string id){
    if(logined_user == NULL)
        throw Login_error();
    Hotel* found_hotel = find_hotel(id);
    if(found_hotel == NULL)
        throw Found_error();
    found_hotel->print();
}

void Trip::add_amount_to_user_wallet(double amount){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->add_amount_to_wallet(amount);
    print_accomplished();
}

void Trip::get_user_transaction(int count){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->get_transaction(count);
}

void Trip::add_comment(std::string hotel_id, std::string comment){
    if(logined_user == NULL)
        throw Login_error();
    Hotel* found_hotel = find_hotel(hotel_id);
    if(found_hotel == NULL)
        throw Found_error();
    found_hotel->add_comment(logined_user, comment);
    print_accomplished();

}
void Trip::get_hotel_comment(std::string hotel_id){
    if(logined_user == NULL)
        throw Login_error();
    Hotel* found_hotel = find_hotel(hotel_id);
    if(found_hotel == NULL)
        throw Found_error();
    found_hotel->print_hotel_comment();
}

void Trip::get_hotel_rate(std::string hotel_id){
    if(logined_user == NULL)
        throw Login_error();
    Hotel* found_hotel = find_hotel(hotel_id);
    if(found_hotel == NULL)
        throw Found_error();
    found_hotel->print_hotel_rate();
}

void Trip::add_rate(std::string hotel_id, double location, double cleanliness, double staff, double facilities, double value_for_money, double overall_rating){
    if(logined_user == NULL)
        throw Login_error();
    Hotel* found_hotel = find_hotel(hotel_id);
    if(found_hotel == NULL)
        throw Found_error();
    Rating* new_rate = new Rating(logined_user, location, cleanliness, staff, facilities, value_for_money, overall_rating);       
    found_hotel->add_rate(logined_user, new_rate);

    print_accomplished();
}

void Trip::print_room_name(std::vector<Room*> rooms){
    for(int i = 0; i < rooms.size(); i++){
        rooms[i]->print_id();
        if(i + 1 != rooms.size())
            std::cout << ' ';
    }
    std::cout << std::endl;
}

void Trip::reserve_room(std::string hotel_id, std::string type_room, int quantity, int check_in, int check_out){
    if(logined_user == NULL)
        throw Login_error();
    Hotel* found_hotel = find_hotel(hotel_id);
    if(found_hotel == NULL)
        throw Found_error();
    Date* date = new Date(check_in, check_out);
    std::vector<Room*> resered_rooms = found_hotel->return_reserve_room(type_room, quantity, date);
    logined_user->submit_reserve(found_hotel->get_id(), resered_rooms, date);
    print_room_name(resered_rooms);   
}

void Trip::see_reserves(){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->print_reserves_info();
}

void Trip::cansel_reserve(int id){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->delete_reserve(id);
    print_accomplished();

}
void Trip::change_hotel_sort(std::string sort_type, std::string command){
    if(logined_user == NULL)
        throw Login_error();
    sort.select_ordering(sort_type, command);
    print_accomplished();
}
void Trip::save_manual_weights(std::string active_condition, double location_w, double cleanliness_w, double staff_w, double facilities_w, double value_for_money_w){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->set_manual_weight(active_condition, location_w, cleanliness_w, staff_w, facilities_w, value_for_money_w);
    print_accomplished();
}
void Trip::inactive_manual_weights(std::string active_condition){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->set_manual_weight_inactive(active_condition);
    print_accomplished();
}
void Trip::get_manual_weights(){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->print_manual_weights();
}

void Trip::get_estimated_weights(){
    if(logined_user == NULL)
        throw Login_error();
    logined_user->print_estimated_weights();
}
