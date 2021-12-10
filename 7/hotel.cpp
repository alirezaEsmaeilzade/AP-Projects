#include "hotel.hpp"
Hotel::Hotel(std::vector <std::string> inputs){
    unique_id = inputs[0];
    property_name = inputs[1];
    hotel_star_rating = std::stoi(inputs[2]);
    hotel_overview = inputs[3];
    property_amenities = split_string(inputs[4], CHARACTER);
    city = inputs[5];
    latitude = std::stof(inputs[6]);
    longitude = std::stof(inputs[7]);
    image_url = inputs[8];
    num_of_standard_rooms = std::stoi(inputs[9]);
    num_of_deluxe_rooms = std::stoi(inputs[10]);
    num_of_luxury_rooms = std::stoi(inputs[11]);
    num_of_premium_rooms = std::stoi(inputs[12]);
    standard_room_price = std::stoi(inputs[13]);
    deluxe_room_price = std::stoi(inputs[14]);
    luxury_room_price = std::stoi(inputs[15]);
    premium_room_price = std::stoi(inputs[16]);
    initialize_room<Standard_room>(num_of_standard_rooms, standard_room_price);
    initialize_room<Delux_room>(num_of_deluxe_rooms, deluxe_room_price);
    initialize_room<Luxury_room>(num_of_luxury_rooms, luxury_room_price);
    initialize_room<Premium_room>(num_of_premium_rooms, premium_room_price);
    price_average = initialize_average();
    room_number = num_of_standard_rooms + num_of_deluxe_rooms + num_of_luxury_rooms + num_of_premium_rooms;
}
Hotel::~Hotel(){
    std::for_each(rooms.begin(), rooms.end(), [](Room* room){delete room;});
    rooms.clear();
    std::for_each(comments.begin(), comments.end(), [](Comment* comment){delete comment;});
    comments.clear();
    std::for_each(ratings.begin(), ratings.end(), [](Rating* rating){delete rating;});
    ratings.clear();
    delete read_rating;
}
bool Hotel::Hotels_id_is_this(std::string id){return this->unique_id == id;}
bool Hotel::your_city_are_this(std::string city){return this->city == city;}
int Hotel::get_hotel_star(){return hotel_star_rating;}
double Hotel::get_hotel_ave_price(){return price_average;}
std::string Hotel::get_id(){return unique_id;}
        
double Hotel::initialize_average(){
    double i = 0;
    if(standard_room_price != 0)
        i++;
    if(deluxe_room_price != 0)
        i++;
    if(luxury_room_price != 0)
        i++;
    if(premium_room_price != 0)
        i++;
    if(i != 0)
        return (standard_room_price + deluxe_room_price + luxury_room_price + premium_room_price) / i;
    else
        return 0;
}
template <typename T>
void Hotel::initialize_room(int number, int price){
    for(int i = 0; i < number; i++){
        T* new_room = new T(std::to_string(i + 1), price);
        rooms.push_back(new_room);
    }
}
std::vector<Room*> Hotel::return_special_room(std::string type_room, int quantity, Date* new_date){
    std::vector<Room*> special_rooms;
    for(int i = 0; i < rooms.size() && quantity > 0; i++){
        if(rooms[i]->your_type_is_this(type_room)){
            if(rooms[i]->are_you_can_reserve_in_this_date(new_date)){
                special_rooms.push_back(rooms[i]);
                quantity--;
            }
        }
    }
    return special_rooms;
}
        
std::vector<Room*> Hotel::return_reserve_room(std::string type_room, int quantity, Date* new_date){
    std::vector<Room*> reserved_rooms = return_special_room(type_room, quantity, new_date);
    if(quantity != reserved_rooms.size())
        throw Room_error();
    return reserved_rooms;
}

bool Hotel::check_have_special_room(std::string type_room, int quantity, Date* date){
    std::vector<Room*> reserved_rooms = return_special_room(type_room, quantity, date);
    if(quantity != reserved_rooms.size())
        return false;
    else
        return true;
}

void Hotel::add_comment(User* user, std::string comment){
    Comment* new_comment = new Comment(user, comment);
    comments.push_back(new_comment);
}
void Hotel::print_hotel_comment(){
    std::for_each(comments.begin(), comments.end(), [](Comment* comment){comment->print();});
}
void Hotel::print_hotel_some_data(){
    std::cout << unique_id << ' ' << property_name << ' ' << hotel_star_rating << ' ' << city << ' ' << room_number << ' ';
    std::cout  << std::fixed << std::setprecision(SETPRECISION_NUMBER) << price_average << std::endl;
}
void Hotel::print_property_anemities(){
    std::cout << "amenities: ";
    for(int i = 0; i < property_amenities.size(); i++){
        std::cout << property_amenities[i];
        if(i + 1 != property_amenities.size())
            std::cout << "|";
    }
    std::cout << std::endl;
}
void Hotel::print(){
    std::cout << unique_id << std::endl << property_name << std::endl;
    std::cout << "star: " << hotel_star_rating << std::endl << "overview: " << hotel_overview << std::endl;
    print_property_anemities();
    std::cout << "city: " << city << std::endl << "latitude: " << std::fixed << std::setprecision(SETPRECISION_NUMBER) << latitude << std::endl;
    std::cout << "longitude: " << std::fixed << std::setprecision(SETPRECISION_NUMBER) << longitude << std::endl;
    std::cout << "#rooms: " << num_of_standard_rooms << ' ' << num_of_deluxe_rooms << ' ' << num_of_luxury_rooms << ' ' << num_of_premium_rooms << std::endl;
    std::cout << "price: " << standard_room_price << ' ' << deluxe_room_price << ' ' << luxury_room_price << ' ' << premium_room_price << std::endl;
}
void Hotel::delete_duplicated_rate(User* user){
    for(int i = 0; i < ratings.size(); i++){
        if(ratings[i]->check_user(user)){
            delete ratings[i];
            ratings.erase(ratings.begin() + i);
            user->delete_duplicated_rate(ratings[i]);
        }
    }

}
void Hotel::add_rate(User* user ,Rating* rating){
    delete_duplicated_rate(user);
    user->add_rate(rating);
    ratings.push_back(rating);
}
std::vector<double> Hotel::calcute_all_rate(){
    std::vector<double> rate_elements(6, 0);
    for(int i = 0; i < ratings.size(); i++){
        rate_elements[0] += ratings[i]->get_location();
        rate_elements[1] += ratings[i]->get_cleanliness();
        rate_elements[2] += ratings[i]->get_staff();
        rate_elements[3] += ratings[i]->get_facilities();
        rate_elements[4] += ratings[i]->get_value_for_money();
        rate_elements[5] += ratings[i]->get_overall_rating();
    }
    return rate_elements;
}
void Hotel::print_hotel_rate(){
    std::vector<double> rate_elements = calcute_all_rate();
    int rate_number = ratings.size();
    if(rate_number == 0){
        read_rating->print();
        return;
    }
    std::cout << "location: " << rate_elements[0] / rate_number << std::endl << "cleanliness: " << rate_elements[1] / rate_number << std::endl;
    std::cout << "staff: " << rate_elements[2] / rate_number << std::endl << "facilities: " << rate_elements[3] << std::endl;
    std::cout << "value for money: " << rate_elements[4] / rate_number << std::endl << "overall rating: " << rate_elements[5] / rate_number << std::endl;
}
std::string Hotel::get_name(){ return property_name;}
std::string Hotel::get_city(){ return city;}
double Hotel::get_standard_price(){return standard_room_price;}
double Hotel::get_delux_price(){return deluxe_room_price;}
double Hotel::get_luxury_price(){return luxury_room_price;}
double Hotel::get_premium_price(){return premium_room_price;}
void Hotel::initialize_rating(std::vector<std::string> datas){
    Read_rating* rate = new Read_rating(datas);
    this->read_rating = rate;
}
double Hotel::hotel_ave_rate(User* logined_user){
    auto find_rate = std::find_if(ratings.begin(), ratings.end(), [=](Rating* rate){return rate->check_user(logined_user);});
    if(find_rate == ratings.end())
        return logined_user->calcut_manual_weight(read_rating->get_rates());
    else
        return (*find_rate)->get_overall_rating();
}


