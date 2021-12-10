#include "command_line.hpp"
void Command_line::print_error(std::string error_massage){
    std::cout << error_massage << std::endl;
}
std::string Command_line::find_data(std::string for_find, std::vector<std::string> input){
    for(int i = 0; i < input.size(); i+=2){
        if(input[i] == for_find)
            return input[i + 1];
    }
    throw Bad_request();
}
std::vector<std::string> Command_line::return_command_data(int command_size, std::vector<std::string> command_part){
    if(command_part.size() != command_size)
        throw Bad_request();
    if(command_part[2] != "?")
        throw Bad_request();
    command_part.erase(command_part.begin(), command_part.begin() + 3);
    return command_part;
}
void Command_line::type_room_filter_command(std::vector<std::string> datas){
    std::string quantity = find_data("quantity", datas);
    std::string check_in = find_data("check_in", datas);
    std::string check_out = find_data("check_out", datas);
    if(!is_integer(quantity) || !is_integer(check_in) || !is_integer(check_out))
        throw Bad_request();
    trip->add_type_filter(find_data("type", datas), std::stoi(quantity), std::stoi(check_in), std::stoi(check_out));
           
}

void Command_line::post_reserve(std::vector<std::string> datas){
    std::string quantity = find_data("quantity", datas);
    std::string check_in = find_data("check_in", datas);
    std::string check_out = find_data("check_out", datas);
    if(!is_integer(quantity) || !is_integer(check_in) || !is_integer(check_out))
        throw Bad_request();
    trip->reserve_room(find_data("hotel", datas), find_data("type", datas), std::stoi(quantity), std::stoi(check_in), std::stoi(check_out));
}

void Command_line::city_filter_command(std::vector<std::string> command_part){
    if(command_part.size() < 5)
        throw Bad_request();
    if(command_part[2] != "?")
        throw Bad_request();
    if(command_part[3] != "city"){
        throw Bad_request();
    }
    std::string city_name("");
    for(int i = 4; i < command_part.size(); i++){
        city_name += command_part[i];
        if(i + 1 != command_part.size())
            city_name += " ";
    }
    trip->add_city_filter(city_name);
}

void Command_line::price_filter_command(std::vector<std::string> datas){
    std::string min_price = find_data("min_price", datas);
    std::string max_price = find_data("max_price", datas);
    if(!is_positive_float(min_price) || !is_positive_float(max_price))
        throw Bad_request();
    trip->add_price_filter(std::stof(min_price), std::stof(max_price));
}

void Command_line::star_filter_command(std::vector<std::string> datas){
    std::string min_star = find_data("min_star", datas);
    std::string max_star = find_data("max_star", datas);
    if(!is_integer(min_star) || !is_integer(max_star))
        throw Bad_request();
    trip->add_star_filter(std::stoi(min_star), std::stoi(max_star));
}


void Command_line::get_rating_command(std::vector<std::string> datas){
    std::string str_location = find_data("location", datas);
    std::string str_cleanliness = find_data("cleanliness", datas);
    std::string str_staff = find_data("staff", datas);
    std::string str_facilities = find_data("facilities", datas);
    std::string str_value_for_rating = find_data("value_for_money", datas);
    std::string str_overall_rating = find_data("overall_rating", datas);
    if(!is_positive_float(str_location) || !is_positive_float(str_cleanliness) || !is_positive_float(str_staff))
        throw Bad_request();
    if(!is_positive_float(str_facilities) || !is_positive_float(str_value_for_rating) || !is_positive_float(str_overall_rating))
        throw Bad_request();
    double location = std::stof(str_location);
    double cleanliness = std::stof(str_cleanliness);
    double staff = std::stof(str_staff);
    double facilities = std::stof(str_facilities);
    double value_for_rating = std::stof(str_value_for_rating);
    double overall_rating = std::stof(str_overall_rating);
    trip->add_rate(find_data("hotel", datas), location, cleanliness, staff, facilities, value_for_rating, overall_rating);
}

void Command_line::get_wallet(std::vector<std::string> datas){
    std::string count = find_data("count", datas);
    if(!is_integer(count))
        throw Bad_request();
    trip->get_user_transaction(std::stoi(count));
}

void Command_line::post_wallet(std::vector<std::string> datas){
    std::string amount = find_data("amount", datas);
    if(!is_positive_float(amount))
        throw Bad_request();
    trip->add_amount_to_user_wallet(std::stof(amount));   
}
void Command_line::save_manual_weight(std::vector<std::string> datas){
    std::string activity = find_data("active", datas);
    double location = std::stof(find_data("location", datas));
    double cleanliness = std::stof(find_data("cleanliness", datas));
    double staff = std::stof(find_data("staff", datas));
    double facilities = std::stof(find_data("facilities", datas));
    double value_for_rating = std::stof(find_data("value_for_money", datas));
    trip->save_manual_weights(activity, location, cleanliness, staff, facilities, value_for_rating);
}
void Command_line::handel_post(std::vector<std::string> command_part){
        if(command_part[1] == "signup"){
            std::vector<std::string> datas = return_command_data(9, command_part);
            trip->add_new_user(find_data("username", datas), find_data("password", datas), find_data("email", datas));
        }
        else if(command_part[1] == "logout"){
            if(command_part.size() != 2)
                throw Bad_request();
            trip->logout();
        }
        else if(command_part[1] == "login"){
            std::vector<std::string> datas = return_command_data(7, command_part);
            trip->login_user(find_data("username", datas), find_data("password", datas));
        }
        else if(command_part[1] == "filters"){
            if(command_part.size() == 7){
                std::vector <std::string> datas = return_command_data(7, command_part);
                if(datas[0] == "min_star" || datas[0] == "max_star")
                    star_filter_command(datas);
                else
                    price_filter_command(datas);
            }
                
            else if(command_part.size() == 11){
                std::vector <std::string> datas = return_command_data(11, command_part);
                type_room_filter_command(datas);    
            }
            else
                city_filter_command(command_part);
        }
        else if(command_part[1] == "comments"){
            std::vector<std::string> datas = return_command_data(7, command_part);
            trip->add_comment(find_data("hotel", datas), find_data("comment", datas));
        }
        else if(command_part[1] == "ratings"){
            std::vector<std::string> datas = return_command_data(17, command_part);
            get_rating_command(datas);
        }
        else if(command_part[1] == "wallet"){
            std::vector<std::string> datas = return_command_data(5, command_part);
            post_wallet(datas);
        }
        else if(command_part[1] == "reserves"){
            std::vector<std::string> datas = return_command_data(13, command_part);
            post_reserve(datas);
        }
        else if(command_part[1] == "default_price_filter"){
            std::vector<std::string> datas = return_command_data(5, command_part);
            trip->change_default_filter(find_data("active", datas));
        }
        else if(command_part[1] == "sort"){
            std::vector<std::string> datas = return_command_data(7, command_part);
            trip->change_hotel_sort(find_data("property", datas), find_data("order", datas));
        }
        else if(command_part[1] == "manual_weights"){
            if(command_part.size() == 5){
                std::vector<std::string> datas = return_command_data(5, command_part);
                trip->inactive_manual_weights(datas[0]);
            }

            std::vector<std::string> datas = return_command_data(15, command_part);
            save_manual_weight(datas);
        }
        else
            throw Bad_request();
}

void Command_line::handel_delete(std::vector<std::string> command_part){
        if(command_part[1] == "filters"){
            if(command_part.size() != 2)
                throw Bad_request();
            trip->delete_filter();
        }
        else if(command_part[1] == "reserves"){
            std::vector<std::string> datas = return_command_data(5, command_part);
            std::string id = find_data("id", datas);
            if(!is_integer(id))
                throw Bad_request();
            trip->cansel_reserve(std::stoi(id));
        }
        else
            throw Bad_request();
}

void Command_line::handel_command(std::string command){
    try{
        std::vector <std::string> command_part = split_string(command , ' ');
        if(command_part.size() <= 1)
            throw Bad_request();
        if(command_part[0] == "POST")
            handel_post(command_part);
        else if(command_part[0] == "GET")
            handel_get(command_part);
        else if(command_part[0] == "DELETE")
            handel_delete(command_part);
        else
            throw Bad_request();
    }
    catch(Run_time_error error){
        print_error(error.what());
    }
    catch(Bad_request error){
        print_error(error.what());
    }
    catch(Login_error error){
        print_error(error.what());
    }
    catch(Insufficient_rating error){
        print_error(error.what());
    }
    catch(Money_error error){
        print_error(error.what());
    }
    catch(Room_error error){
        print_error(error.what());
    }
    catch(Empty_data_error error){
        print_error(error.what());
    }
    catch(Found_error error){
        print_error(error.what());
    }
    catch(Rate_error error){
        print_error(error.what());
    }
}

void Command_line::handel_get(std::vector <std::string> command_part){
        if(command_part[1] == "hotels"){
            if(command_part.size() == 5){
                if(command_part[2] != "?" || command_part[3] != "id")
                    throw Bad_request();
                trip->print_hotel_by_id(command_part[4]);
            }
            else if(command_part.size() == 2)
                trip->print_all_hotel();
            else
                throw Bad_request();
        }
        else if(command_part[1] == "comments"){
            std::vector<std::string> datas = return_command_data(5, command_part);
            trip->get_hotel_comment(find_data("hotel", datas));
        }
        else if(command_part[1] == "ratings"){
            std::vector<std::string> datas = return_command_data(5, command_part);
            trip->get_hotel_rate(find_data("hotel", datas));
        }
        else if(command_part[1] == "wallet"){
            std::vector<std::string> datas = return_command_data(5, command_part);
            get_wallet(datas);
        }
        else if(command_part[1] == "reserves"){
            if(command_part.size() != 2)
                throw Bad_request();
            trip->see_reserves();
        }
        else if(command_part[1] == "manual_weights"){
            if(command_part.size() != 2)
                throw Bad_request();
            trip->get_manual_weights();
        }
        else if(command_part[1] == "estimated_weights"){
            if(command_part.size() != 2)
                throw Bad_request();
            trip->get_estimated_weights();
        }
        else
            throw Bad_request();
}
