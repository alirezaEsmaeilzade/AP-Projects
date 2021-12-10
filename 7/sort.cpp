#include "sort.hpp"
Sort::Sort(){
    sort_type = "id";
    sorts["id"] = &sort_by_id;
    sorts["name"] = &sort_by_name;
    sorts["star_rating"] = &sort_by_star_rating;
    sorts["city"] = &sort_by_city;
    sorts["standard_room_price"] = &sort_by_standard_room_price;
    sorts["deluxe_room_price"] = &sort_by_delux_room_price;
    sorts["luxury_room_price"] = &sort_by_luxury_room_price;
    sorts["premium_room_price"] = &sort_by_premium_room_price;
    sorts["average_room_price"] = &sort_by_average_room_price;
    ording = true;
}
std::vector<Hotel*> Sort::sort(std::vector<Hotel*> disordered_hotels, User* logined_user){
    std::string sort_type = this->sort_type;
    auto it = std::find_if(sorts.begin(), sorts.end(), [=](std::pair<std::string, std::vector<Hotel*> (*)(std::vector<Hotel*>, bool)> p){return p.first == sort_type;});
    if(sort_type != "id")
        std::sort(disordered_hotels.begin(), disordered_hotels.end(), [=](Hotel* alpha, Hotel* beta){return alpha->get_id() < beta->get_id();});
    if(it == sorts.end())
        return manual_sort(disordered_hotels, logined_user, ording);
    return (it->second)(disordered_hotels, ording);
}
std::vector<Hotel*> Sort::manual_sort(std::vector<Hotel*> input, User* logined_user, bool ordering){
    if(logined_user->manual_weight_activity() || logined_user->is_estimated_condition_ok()){
        if(!logined_user->manual_weight_activity() && logined_user->is_estimated_condition_ok())
            logined_user->estimate_weights();
        auto conditoin = [=](Hotel* alpha, Hotel* beta){return (alpha->hotel_ave_rate(logined_user) < beta->hotel_ave_rate(logined_user)) == ordering;};
        std::stable_sort(input.begin(), input.end(), conditoin);
    }
    return input;
}
void Sort::select_ordering(std::string sort_type, std::string ordering_type){
    if(ordering_type != "ascending" && ordering_type != "descending")
        throw Bad_request();
    if(ordering_type == "ascending")
        ording = true;
    if(ordering_type == "descending")
        ording = false;
    if(!std::any_of(sorts.begin(), sorts.end(), [=](std::pair<std::string, std::vector<Hotel*> (*)(std::vector<Hotel*>, bool)> p){return p.first == sort_type;}) && sort_type != "rating_personal")
        throw Bad_request();
    this->sort_type = sort_type;
}
std::vector<Hotel*> Sort::sort_by_id(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_id() < beta->get_id()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_name(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_name() < beta->get_name()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_city(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_city() < beta->get_city()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_star_rating(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_hotel_star() < beta->get_hotel_star()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_standard_room_price(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_standard_price() < beta->get_standard_price()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_delux_room_price(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_delux_price() < beta->get_delux_price()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_luxury_room_price(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_luxury_price() < beta->get_luxury_price()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_premium_room_price(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_premium_price() < beta->get_premium_price()) == ordering;});
    return input;
}
std::vector<Hotel*> Sort::sort_by_average_room_price(std::vector<Hotel*> input, bool ordering){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return (alpha->get_hotel_ave_price() < beta->get_hotel_ave_price()) == ordering;});
    return input;
}
std::vector<Hotel*> sort_by_average_room_price(std::vector<Hotel*> input, User* logined_user){
    std::stable_sort(input.begin(), input.end(), [=](Hotel* alpha, Hotel* beta){return alpha->get_hotel_ave_price() < beta->get_hotel_ave_price();});
    return input;
}

