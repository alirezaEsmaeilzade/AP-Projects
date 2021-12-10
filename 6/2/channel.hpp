#ifndef __CHANNEL_H__
#define __CHANNEL_H__
#include <string>
#include <vector>
class Robot;
class Channel{
    public:
        Channel(std::string name);
        void attach(Robot* robot){
            robots.push_back(robot);
        }
        void set_massage(std::string new_massage);
        bool send_or_no(){return sended_to_echo;}
        std::string get_new_massage(){return massages[massages.size() - 1];}
        bool your_name_is_this(std::string name){return this->name == name;}
        void sended_to_echo_robot(){sended_to_echo = false;}
        void writed_in_file(){write_in_file_or_no = false;}
        void notify();
    private:
        std::vector < class Robot* > robots;
        std::vector <std::string> massages;
        std::string name;
        bool sended_to_echo;
        bool write_in_file_or_no;
};
#endif