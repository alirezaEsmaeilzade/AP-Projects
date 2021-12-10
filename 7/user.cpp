#include "user.hpp"
#include "rating.hpp"
User::User(std::string username, std::string password, std::string email){
    this->username = username;
    this->password = generate_password_hash(password);
    this->email = email;
    amount = 0;
    transaction.push_back(amount);
    estimated_weight = false;
}

User::~User(){
    std::for_each(reserves.begin(), reserves.end(), [](Reserve* reserve){delete reserve;});
    reserves.clear();
}

unsigned long int User::generate_password_hash(std::string  password){
    return std::hash<std::string>() (password);
}

bool User::your_password_is_this(std::string password){return generate_password_hash(password) == this->password;}
bool User::your_email_is_this(std::string email){
    return email == this->email;
}

void User::print_username_for_comment(){
    std::cout << username << ": ";
}

double User::calcute_room_price(std::vector<Room*> rooms, Date* date){
    double total_price = 0;
    for(int i = 0; i < rooms.size(); i++)
       total_price += rooms[i]->get_price() * date->get_reserve_long();
    return total_price;
}

void User::pay_hotel_cast(double cast){
    if(amount < cast)
        throw Money_error();
    amount -= cast;
    transaction.push_back(amount);
}

bool User::your_username_is_this(std::string username){return username == this->username;}
void User::add_amount_to_wallet(double amount){
    if(amount <= 0)
        throw Bad_request();
    this->amount += amount;
    transaction.push_back(this->amount);
}

void User::get_transaction(int count){
    if(count <= 0){
        throw Bad_request();
    }
    for(int i = 0; i < count && i < transaction.size(); i++){
        int convert = transaction[transaction.size() - i - 1];
        std::cout << convert << std::endl;
    }
}

void User::submit_reserve(std::string hotel_id, std::vector<Room*> rooms, Date* reserve_date){
    int id = reserves.size() + 1;
    double cost = calcute_room_price(rooms, reserve_date);
    pay_hotel_cast(cost);
    Reserve* new_reserve = new Reserve(hotel_id, reserve_date, cost, rooms, id);
    std::for_each(rooms.begin(), rooms.end(), [=](Room* room){room->reserve(reserve_date);});
    reserves.push_back(new_reserve);
}

void User::print_reserves_info(){
    for(int i = 0; i < reserves.size(); i++){
        reserves[reserves.size() - i - 1]->print();
        std::cout << std::endl;
    }
}

Reserve* User::find_reserve(int id){
    auto it = std::find_if(reserves.begin(), reserves.end(), [=](Reserve* reserve){return reserve->your_id_is_this(id);});
    if(it != reserves.end())
        return *it;
    return NULL;
}

void User::delete_reserve(int id){
    Reserve* found_reserve = find_reserve(id);
    if(found_reserve == NULL)
        throw Found_error();
    add_amount_to_wallet(found_reserve->get_cansel_cost());
    found_reserve->cansel_reserve();
    delete_reserve_from_vector(found_reserve);            
}

void User::delete_reserve_from_vector(Reserve* for_delete){
    for(int i = 0; i < reserves.size(); i++){
        if(for_delete == reserves[i]){
            delete for_delete;
            reserves.erase(reserves.begin() + i);
        }
    }
}

int User::get_reserves_num(){ return reserves.size();}

double User::return_standard_deviation(){
    double cost_ave = return_ave();
    double sum = std::accumulate(reserves.begin(), reserves.end(), 0.0, [=](double sum, Reserve* reserve){ return sum + std::pow(cost_ave - reserve->get_each_room_price(), 2);});
    return std::sqrt(sum / (reserves.size() - 1));
}

double User::return_ave(){
    double cost_sum = std::accumulate(reserves.begin(), reserves.end(), 0.0, [](double sum, Reserve* reserve){ return sum + reserve->get_cost();});
    int room_number = std::accumulate(reserves.begin(), reserves.end(), 0, [](int sum, Reserve* reserve){return sum + reserve->get_room_number();});
    if(room_number == 0)
        return 0;
    return cost_sum / room_number;
}
void User::set_manual_weight(std::string acctivity_conditoin, double location_w, double cleanliness_w, double staff_w, double facilities_w, double value_for_money_w){
    weights.set_rating_weights(location_w, cleanliness_w, staff_w, facilities_w, value_for_money_w);
    weights.set_activity_condition(acctivity_conditoin);
}
void User::set_manual_weight_inactive(std::string acctivity_conditoin){
    weights.set_activity_condition(acctivity_conditoin);
}
double User::calcut_manual_weight(std::vector< double> rates){
    return f(rates, weights.get_double_elements());
}

void User::add_rate(Rating* new_rate){
    ratings.push_back(new_rate);
    estimated_weight = false;
}
void User::delete_duplicated_rate(Rating* duplicate){
    ratings.erase(std::remove_if(ratings.begin(), ratings.end(), [=](Rating* rate){return duplicate == rate;}), ratings.end());
    estimated_weight = false;
}
void User::print_manual_weights(){
    weights.print();
}
double User::f(std::vector<double> x, std::vector<double> w){
    std::vector<double> weights_rates = w;
    for(int i = 0; i < weights_rates.size(); i++)
        weights_rates[i] *= x[i];
    double sum_weight_rate = std::accumulate(weights_rates.begin(), weights_rates.end(), 0.0, [=](double sum, double weight){return sum + weight;});
    double sum_weight = std::accumulate(w.begin(), w.end(), 0.0, [=](double sum, double weight){return sum + weight;});
    return sum_weight_rate / sum_weight;
}
double User::E(std::vector<double> x, std::vector<double> w, double y){
    return std::pow(f(x, w) - y, 2);
}
std::vector<double> add_num_to_vector(std::vector<double> vec, int index, double num){
    if(index < 5 && index >= 0)
        vec[index] += num;
    return vec;
}
double User::E_partial_derivative(std::vector<double> x, std::vector<double> w, int index, double y){
    return (E(x, add_num_to_vector(w, index, EPSILON), y) - E(x, w, y)) / EPSILON;
}
double clamp(double x, int a, int b){
    if(x < a)
        return a;
    if(x > b)
        return b;
    return x;
}
void User::estimate_weights(){
    if(estimated_weight)
        return;
    if(ratings.size() < 5)
        throw Insufficient_rating();
    std::vector<double> w;
    std::srand(std::time(0));
    for(int i = 0; i < 5; i++)
        w.push_back((rand() % 4) + 1);
    for(int k = 0; k < 1000; k++){
        std::vector<double> d(5, 0);
        for(int j = 0; j < ratings.size(); j++){
            for(int i = 0; i < 5; i++){
                d[i] += E_partial_derivative(ratings[j]->get_rating(), w, i, ratings[j]->get_overall_rating());
            }   
        }
        for(int i = 0; i < 5; i++){
            w[i] = w[i] - 1 * d[i];
            w[i] = clamp(w[i], 1, 5);
        }
    }
    weights.set_estimulat_weight(w);
    estimated_weight = true;
}
void User::print_estimated_weights(){
    estimate_weights();
    weights.print_estimated();
}
bool User::manual_weight_activity(){return weights.activity_condition();}
bool User::is_estimated_condition_ok(){return ratings.size() >= 5;}
        