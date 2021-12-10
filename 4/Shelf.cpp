#include "Shelf.h"
bool compare_name(Book a, Book b){
    return (a.get_title() < b.get_title());
}
void Shelf::show_sorted_shelf(std::string shelf_type, std::string genre){
    std::vector<Book> gerned;
    std::vector<Book> alphebeticaly;
    if(shelf_type == "read"){
        for(int i = 0; i < read.size(); i++){
            if(read[i]->is_genre_true(genre))
                gerned.push_back(*read[i]);
            else
                alphebeticaly.push_back(*read[i]);
        }
    }
    else if(shelf_type == "currently_reading"){
        for(int i = 0; i < currently_reading.size(); i++){
            if(currently_reading[i]->is_genre_true(genre))
                gerned.push_back(*currently_reading[i]);
            else
                alphebeticaly.push_back(*currently_reading[i]);
        }
    }
    else{
        for(int i = 0; i < want_to_read.size(); i++){
            if(want_to_read[i]->is_genre_true(genre))
                gerned.push_back(*want_to_read[i]);
            else
                alphebeticaly.push_back(*want_to_read[i]);            
        }
    }
    sort(gerned.begin(), gerned.end(), compare_name);
    sort(alphebeticaly.begin(), alphebeticaly.end(), compare_name);
    for(int i = 0; i < gerned.size(); i++)
        gerned[i].print_book_for_shelf();
    for(int i = 0; i < alphebeticaly.size(); i++)
        alphebeticaly[i].print_book_for_shelf();
}
void Shelf::print(){
    std::cout<< "Number of Books in Read Shelf: " << read.size() << std::endl;
    std::cout<< "Number of Books in Want to Read Shelf: " << want_to_read.size() << std::endl;
    std::cout<< "Number of Books in Currently Reading Shelf: " << currently_reading.size() << std::endl;
}
