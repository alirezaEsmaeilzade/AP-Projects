#include "massager.hpp"
Massager::~Massager(){
    for(int i = 0; i < robots.size(); i++)
        delete robots[i];
    for(int i = 0; i < channels.size(); i++)
        delete channels[i];
}
void Massager::add_channel(std::string name){
    try{
        for(int i = 0; i < channels.size(); i++){
            if(channels[i]->your_name_is_this(name))
                throw Run_time_error("Channel already exists");
        }
        Channel* new_channel = new Channel(name);
        channels.push_back(new_channel);
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}
void Massager::tell_massage(std::string channel_name, std::string massage){
    try{
        Channel* find_channel = find_channel_by_name(channel_name);
        if(find_channel == NULL)
            throw Run_time_error("Channel does not exist");
        find_channel->set_massage(massage);
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}
void Massager::add_fred_robot(std::string channel_name){
    try{
        Channel* robot_channel = find_channel_by_name(channel_name);
        if(robot_channel == NULL)
            throw Run_time_error("Channel does not exist");
        Fred_robot* robot = new Fred_robot(robot_channel);
        robots.push_back(robot);
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}
void Massager::add_librarian_robot(std::string channel_name){
    try{
        Channel* find_channel = find_channel_by_name(channel_name);
        if(find_channel == NULL)
            throw Run_time_error("Channel does not exist");
        Librarian_robot* robot = new Librarian_robot(find_channel);
        robots.push_back(robot);
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}
void Massager::add_echo_robot(std::string src_channel_name, std::string dest_channel_name){
    try{
        Channel* src_channel = find_channel_by_name(src_channel_name);
        Channel* dest_channel = find_channel_by_name(dest_channel_name);
        if(src_channel == NULL || dest_channel == NULL)
            throw Run_time_error("Channel does not exist");
        if(src_channel == dest_channel){
            throw Run_time_error("Source and Destination cannot be the same channel");
        }
        Echo_robot* robot = new Echo_robot(src_channel, dest_channel);
        robots.push_back(robot);
    }
    catch(Run_time_error error){
        std::cerr << error.what() << std::endl;
    }
}
void Massager::add_logger_robot(std::string file_name){
    Logger_robot* robot = new Logger_robot(file_name, channels);
        robots.push_back(robot);
}
Channel* Massager::find_channel_by_name(std::string name){
    for(int i = 0; i < channels.size(); i++){
        if(channels[i]->your_name_is_this(name)){
            return channels[i];
        }
    }
    return NULL;
}