#include "manual_weight.hpp"
Manual_weights::Manual_weights(){
    elements.push_back(std::make_pair("location", INITIALIZE_WIGHT));
    elements.push_back(std::make_pair("cleanliness", INITIALIZE_WIGHT));
    elements.push_back(std::make_pair("staff", INITIALIZE_WIGHT));
    elements.push_back(std::make_pair("facilities", INITIALIZE_WIGHT));
    elements.push_back(std::make_pair("value_for_money", INITIALIZE_WIGHT));
    this->activity = false;
}
void Manual_weights::set_rating_weights(double location_w, double cleanliness_w, double staff_w, double facilities_w, double value_for_money_w){
    if(!check_input(location_w) && !check_input(cleanliness_w) && !check_input(staff_w) && !check_input(facilities_w) && !check_input(value_for_money_w))
        throw Bad_request();
    elements[0].second = location_w;
    elements[1].second = cleanliness_w;
    elements[2].second = staff_w;
    elements[3].second = facilities_w;
    elements[4].second = value_for_money_w;
}
void Manual_weights::set_estimulat_weight(std::vector<double> est_weight){
    for(int i = 0; i < elements.size(); i++)
        elements[i].second = est_weight[i];
}
void Manual_weights::set_activity_condition(std::string acctivity_conditoin){
    if(acctivity_conditoin != "true" && acctivity_conditoin != "false")
        throw Bad_request();
    if(acctivity_conditoin == "true")
        activity = true;
    else
        activity = false;
}
void Manual_weights::print(){
    if(activity){
        std::cout << "active " << std::boolalpha << activity << ' ';
        auto lamda = [](std::pair<std::string, double> element){std::cout << element.first << ' ' << std::fixed << std::setprecision(SETPRECISION_NUMBER) << element.second << ' ';};
        std::for_each(elements.begin(), elements.end(), lamda);
        std::cout << std::endl;
    }
    else
        std::cout << "active " << std::boolalpha << activity << ' ';
}
void Manual_weights::print_estimated(){
    std::for_each(elements.begin(), elements.end(), [](std::pair<std::string, double> element){std::cout << element.first << ": " << element.second << ' ';});
}
bool Manual_weights::activity_condition(){return activity;}
bool Manual_weights::check_input(double input){return input >= 1 && input <= 5;}
manual_weights_elements Manual_weights::get_elements(){return elements;}
std::vector<double> Manual_weights::get_double_elements(){
    std::vector<double> double_elements;
    std::transform(elements.begin(), elements.end(), back_inserter(double_elements), [](std::pair<std::string, double> const &p){return p.second;});
    return double_elements;
}
        