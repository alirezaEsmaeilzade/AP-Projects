#ifndef __SORT_H__
#define __SORT_H__
#include "hotel.hpp"
#include "user.hpp"
#include "error.hpp"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
class Sort{
    public:
        Sort();
        std::vector<Hotel*> sort(std::vector<Hotel*> disordered_hotels, User* logined_user);
        std::vector<Hotel*> manual_sort(std::vector<Hotel*> input, User* logined_user, bool ordering);
        void select_ordering(std::string sort_type, std::string ordering_type);
    private:
        static std::vector<Hotel*> sort_by_id(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_name(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_star_rating(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_city(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_standard_room_price(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_delux_room_price(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_luxury_room_price(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_premium_room_price(std::vector<Hotel*> input, bool ordering);
        static std::vector<Hotel*> sort_by_average_room_price(std::vector<Hotel*> input, bool ordering);
        std::vector<Hotel*> sort_by_average_room_price(std::vector<Hotel*> input, User* logined_user);

        std::map<std::string, std::vector<Hotel*> (*)(std::vector<Hotel*>, bool)> sorts;
        std::string sort_type;
        bool ording;
};
#endif