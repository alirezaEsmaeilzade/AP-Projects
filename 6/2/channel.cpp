#include "channel.hpp"
#include "robots.hpp"
Channel::Channel(std::string name){
    this->name = name;
    sended_to_echo = false;
    write_in_file_or_no = false;
}
void Channel::set_massage(std::string new_massage){
    if(new_massage.front() == ' ')
        new_massage.erase(new_massage.begin());
    massages.push_back(new_massage);
    sended_to_echo = true;
    write_in_file_or_no = true;
    notify();
}
void Channel::notify(){
    for(int i = 0; i < robots.size(); i++){
        robots[i]->update();
    }
}