#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "Goodread.h"

using namespace std;


void command(Good_read* good_read){
    string command;
    while(cin>>command){
        if(command == "show_author_info"){
            int id;
            cin>>id;
            good_read->show_author_info(id);
        }
        else if(command == "show_sorted_shelf"){
            int user_id;
            string shelf_type, genre;
            cin>> user_id >> shelf_type >> genre;
            good_read->show_user_shelf(user_id, shelf_type, genre);
        }
        else if(command == "credit"){
            int user_id;
            cin>> user_id;
            good_read->show_user_credit(user_id);
        }
        else if(command == "best_book")
            good_read->find_best_book();
        else if(command == "best_reviewer")
            good_read->find_best_user();
        else if(command == "recommend_first_approach"){
            int user_id;
            cin>> user_id;
            good_read->suggest_first_book(user_id);
        }
        else if(command == "recommend_second_approach"){
            int user_id;
            cin>>user_id;
            good_read->suggest_second_book(user_id);
        }
        else
            break;
    }
}
int main(int argc, char *argv[]){
    Good_read good_read(argv[1]);
    command(&good_read);
    return 0;
}