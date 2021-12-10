#ifndef __COMMAND_LINE_H__
#define __COMMAND_LINE_H__
#include "trip.hpp"
class Command_line{
    public:
        Command_line(Trip* trip){
            this->trip = trip;
        }
        void print_error(std::string error_massage);
        void handel_command(std::string command);
        void handel_post(std::vector <std::string> command_part);
        void handel_get(std::vector <std::string> command_part);
        void handel_delete(std::vector<std::string> command_part);
        std::vector<std::string> return_command_data(int command_size, std::vector<std::string> command_part);
    private:
        void get_rating_command(std::vector<std::string> datas);
        void post_wallet(std::vector<std::string> datas);
        void star_filter_command(std::vector<std::string> datas);
        void price_filter_command(std::vector<std::string> datas);
        void city_filter_command(std::vector<std::string> command_part);
        void type_room_filter_command(std::vector<std::string> datas);
        void post_reserve(std::vector<std::string> datas);
        void get_wallet(std::vector<std::string> datas);
        void save_manual_weight(std::vector<std::string> datas);
        std::string find_data(std::string for_find, std::vector<std::string> input);
        Trip* trip;
};
#endif