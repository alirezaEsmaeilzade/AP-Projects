#include "User.h"

bool compare_by_id(Author a, Author b){
    return (a.get_id() < b.get_id());
}
bool User::is_id_correct(int id){
    if(this->id == id)
        return true;
    return false;
}
void User::print_favorite_author(){
    std::cout<< "Favorite Authors: ";
    std::vector<Author> sorted_favorite_authors;
    for(int i = 0; i < favorite_authors.size(); i++)
        sorted_favorite_authors.push_back(*favorite_authors[i]);
    sort(sorted_favorite_authors.begin(), sorted_favorite_authors.end(), compare_by_id);
    for(int i = 0; i < sorted_favorite_authors.size(); i++){
        std::cout<< sorted_favorite_authors[i].get_name();
        if(i != sorted_favorite_authors.size() - 1)
            std::cout<< ", ";
    }
    std::cout<< std::endl;
}
void User::print(){
    std::cout <<"id: "<< id << std::endl << "Name: "<< name << std::endl<< "Place of Birth: " << place_of_birth << std::endl << "Member Since: "<< member_since << std::endl;
    std::cout<< "Favorite Genres: ";
    print_sorted_string_vector(favorite_genre); 
    print_favorite_author();
    shelf.print();
    std::cout<< "Number of Likes: " << get_like_numbers() << std::endl;
}