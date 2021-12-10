#include "rating.hpp"
Rating::Rating(User* user, double location, double cleanliness, double staff, double facilities, double value_for_money, double overall_rating){
    if(!check_number(location) || !check_number(cleanliness) || !check_number(staff))
        throw Bad_request();
    if(!check_number(facilities) || !check_number(value_for_money) || !check_number(overall_rating))
        throw Bad_request();
    elements.push_back(std::make_pair("location", location));
    elements.push_back(std::make_pair("cleanliness", cleanliness));
    elements.push_back(std::make_pair("staff", staff));
    elements.push_back(std::make_pair("facilities", facilities));
    elements.push_back(std::make_pair("value_for_money", value_for_money));
    elements.push_back(std::make_pair("overall_rating", overall_rating));
    this->user = user;
}
std::vector<double> Rating::get_rating(){
    std::vector<double> double_elements;
    std::transform(elements.begin(), elements.end(), back_inserter(double_elements), [](std::pair<std::string, double> const &p){return p.second;});
    double_elements.pop_back();
    return double_elements;
}
bool Rating::check_user(User* user){ return this->user == user;}
bool Rating::check_number(double input_rate){ return 1 <= input_rate && input_rate <= 5; }
double Rating::get_location(){return elements[0].second;}
double Rating::get_cleanliness(){return elements[1].second;}
double Rating::get_staff(){return elements[2].second;}
double Rating::get_facilities(){return elements[3].second;}
double Rating::get_value_for_money(){return elements[4].second;}
double Rating::get_overall_rating(){return elements[5].second;}
Read_rating::Read_rating(std::vector<std::string> input){
    elements.push_back(std::make_pair("location", std::stof(input[0])));
    elements.push_back(std::make_pair("cleanliness", std::stof(input[1])));
    elements.push_back(std::make_pair("staff", std::stof(input[2])));
    elements.push_back(std::make_pair("facilities", std::stof(input[3])));
    elements.push_back(std::make_pair("value_for_money", std::stof(input[4])));
    elements.push_back(std::make_pair("overall_rating", std::stof(input[5])));
}
void Read_rating::print(){
    auto lamda = [](std::pair<std::string, double> element){std::cout << element.first << ": " << std::fixed << std::setprecision(SETPRECISION_NUMBER) <<element.second << std::endl;};
    std::for_each(elements.begin(), elements.end(), lamda);
}
double Read_rating::get_overall_rating(){return elements[5].second;}
std::vector<double> Read_rating::get_rates(){
    std::vector<double> double_elements;
    std::transform(elements.begin(), elements.end(), back_inserter(double_elements), [](std::pair<std::string, double> const &p){return p.second;});
    return double_elements;
}