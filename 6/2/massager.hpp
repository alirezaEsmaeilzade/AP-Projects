#ifndef __MASSAGER_H__
#define __MASSAGER_H__
#include <string>
#include <vector>
#include <iostream>
#include "channel.hpp"
#include "robots.hpp"
#include "error.hpp"

class Massager{
    public:
        ~Massager();
        void add_channel(std::string name);
        void tell_massage(std::string channel_name, std::string massage);
        void add_fred_robot(std::string channel_name);
        void add_librarian_robot(std::string channel_name);
        void add_echo_robot(std::string src_channel_name, std::string dest_channel_name);
        void add_logger_robot(std::string file_name);
    private:
        Channel* find_channel_by_name(std::string name);
        std::vector <Channel*> channels;
        std::vector <Robot*> robots;
};
#endif