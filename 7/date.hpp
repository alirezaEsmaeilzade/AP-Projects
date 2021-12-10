#ifndef __DATE_H__
#define __DATE_H__
#include "error.hpp"
class Date{
    public:
        Date(int start, int end);
        bool check_interference(Date* input);
        int get_reserve_long();
        int get_start();
        int get_end();
    private:
        bool check_contain_this_day(int day);
        bool check_date(int first_day, int second_day);
        int start;
        int end;
};

#endif