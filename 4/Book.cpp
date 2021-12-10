#include "Book.h"

bool Book::is_author_id_true(int id){
    if(author_of_book->is_id_correct(id))
        return true;
    return false;
}
bool Book::is_id_true(int id){
    if(this->id == id)
        return true;
    return false;
}
bool Book::is_genre_true(std::string unchecked_genre){
    if(genre == unchecked_genre)
        return true;
    return false;
}
void Book::print_book_info_for_author(){
    std::cout<< "id: " << id << ' ' << "Title: " << title << std::endl;
}
void Book::print_book_for_shelf(){
    std::cout<< "id: " << id << std::endl << "Title: " << title << std::endl;
    std::cout<< "Genre: "<< genre << std::endl << "Author: "<< author_of_book->get_name()<< std::endl;
    std::cout<<"***"<<std::endl;
}
void Book::print_book_info(){
    std::cout<< "id: " << id << std::endl << "Title: " << title << std::endl;
    std::cout<< "Genre: "<< genre << std::endl << "Author: "<< author_of_book->get_name()<< std::endl;
    std::cout<< "Average Rating: ";
    std::cout<< std::fixed << std::setprecision(2) << get_average_of_rateing() << std::endl;
}
void Book::print_book_for_suggest(){
    std::cout<< "id: " << id << std::endl << "Title: " << title << std::endl;
    std::cout<< "Genre: "<< genre << std::endl << "Author: "<< author_of_book->get_name()<< std::endl;
}
double Book::comput_score(std::vector <std::string> favorite_genre){
    for(std::string check : favorite_genre){
        if(check == genre)
            return 5 + average_of_special_rate;
    }
    return average_of_special_rate;
}