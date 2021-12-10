#include "error.hpp"
Run_time_error::Run_time_error(std::string error_massage){
    this->error_massage = error_massage;
}
const char* Run_time_error::what(){
    return this->error_massage.c_str();
}