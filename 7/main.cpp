#include "trip.hpp"
#include "command_line.hpp"
#include <string>
#include <iostream>
int main(int argc, char *argv[]){
    Trip trip(argv[1], argv[2]);
    Command_line command_line(&trip);
    std::string command;
    while(std::getline(std::cin, command, '\n')){
        command_line.handel_command(command);
    }
}