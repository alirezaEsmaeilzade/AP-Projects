#include "functions.hpp"
void commands(Massager* massager){
    while(true){
        std::string command;
        std::string channel_name;
        std::string robot_name;
        std::cin >> command;
        if(command == "add_channel"){
            std::cin >> channel_name;
            massager->add_channel(channel_name);
        }
        else if(command == "add_bot"){
            std::cin >> robot_name;
            if(robot_name == "logger"){
                std::string file_name;
                std::cin >> file_name;
                massager->add_logger_robot(file_name);
            }
            else if(robot_name == "fred"){
                std::cin >> channel_name;
                massager->add_fred_robot(channel_name);
            }
            else if(robot_name == "echo"){
                std::string second_channel_name;
                std::cin >> channel_name;
                std::cin >> second_channel_name;
                massager->add_echo_robot(channel_name, second_channel_name);
            }
            else if(robot_name == "librarian"){
                std::cin >> channel_name;
                massager->add_librarian_robot(channel_name);
            }
        }
        else if(command == "tell"){
            std::string massage;
            std::cin >> channel_name;
            std::getline(std::cin, massage);
            massager->tell_massage(channel_name, massage);
        }
    }
}
