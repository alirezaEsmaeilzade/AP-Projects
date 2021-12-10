#include "date.hpp"
Date::Date(int start, int end){
    if(check_date(start, end))
        throw Run_time_error(BAD_REQUEST);
    this->start = start;
    this->end = end;
}

int Date::get_start(){return start;}
int Date::get_end(){return end;}
bool Date::check_date(int first_day, int second_day){
    return first_day < 1 || first_day > 30 || second_day < 1 || second_day > 30;
}

bool Date::check_interference(Date* input){
    if(!check_contain_this_day(input->get_start()) || !check_contain_this_day(input->get_end()))
        return false;
    return true;
}

bool Date::check_contain_this_day(int day){ 
    if(start < end)
        return start < day && day < end;
    else if(start > end)
        return !(end < day && day < start);
}

int Date::get_reserve_long(){
    if(start < end)
        return end - start + 1;
    else if(start > end)
        return 30 - start + end + 1;
}
