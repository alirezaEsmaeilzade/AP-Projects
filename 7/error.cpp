#include "error.hpp"
Run_time_error::Run_time_error(std::string error_massage){
    this->error_massage = error_massage;
}
const char* Run_time_error::what(){
    return this->error_massage.c_str();
}
Bad_request::Bad_request(){
    this->error_massage = BAD_REQUEST;
}
const char* Bad_request::what(){
    return this->error_massage.c_str();
}
Login_error::Login_error(){
    this->error_massage = LOGINE_ERROR;
}
const char* Login_error::what(){
    return this->error_massage.c_str();
}
Found_error::Found_error(){
    this->error_massage = FOUND_ERROR;
}
const char* Found_error::what(){
    return this->error_massage.c_str();
}
Money_error::Money_error(){
    this->error_massage = MONEY_ERROR;
}
const char* Money_error::what(){
    return this->error_massage.c_str();
}
Rate_error::Rate_error(){
    this->error_massage = RATE_ERROR;
}
const char* Rate_error::what(){
    return this->error_massage.c_str();
}
Insufficient_rating::Insufficient_rating(){
    this->error_massage = INSUFFICIENT_RATING;
}      
const char* Insufficient_rating::what(){
    return this->error_massage.c_str();
}
Room_error::Room_error(){
    this->error_massage = ROOM_ERROR;
}      
const char* Room_error::what(){
    return this->error_massage.c_str();
}
Empty_data_error::Empty_data_error(){
    this->error_massage = EMPTY_DATA;
}      
const char* Empty_data_error::what(){
    return this->error_massage.c_str();
}
