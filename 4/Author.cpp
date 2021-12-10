#include "Author.h"
void Author::initialize(std::string input){
    std::vector<std::string> splited_part = split_string(input, separator_one);
    id = stoi(splited_part[0]);
    name = splited_part[1];
    gender = splited_part[2];
    member_since = splited_part[3];
    year_of_birth = stoi(splited_part[4]);
    place_of_birth = splited_part[5];
    genres = split_string(splited_part[6], separator_two);
}
void Author::print(){
    std::cout<< "id: "<< id << std::endl << "Name: " << name << std::endl;
    std::cout<< "Year of Birth: " << year_of_birth << std::endl << "Place of Birth: " << place_of_birth << std::endl;
    std::cout<< "Member Since: " << member_since << std::endl  <<"Genres: ";
    print_sorted_string_vector(genres);
}
bool Author::is_id_correct(int id){
    if(this->id == id)
        return true;
    return false;
}
