#ifndef _SHELF_H_
#define _SHELF_H_
#include "functions.h"
#include "Book.h"
#include <string>
#include <vector>
#include <algorithm>

bool compare_name(Book a, Book b);

class Shelf{
    public:
        void add_want_to_read(Book* whant_to_read_member){
            want_to_read.push_back(whant_to_read_member);
        }
        void add_currently_read(Book* currently_reading_member){
            currently_reading.push_back(currently_reading_member);
        }
        void add_read(Book* read_member){
            read.push_back(read_member);
        }
        void show_sorted_shelf(std::string shelf_type, std::string genre);
        std::vector<Book*> get_read(){return read;}
        void print();
    private:
        
        std::vector <Book*> want_to_read;
        std::vector <Book*> currently_reading;
        std::vector <Book*> read;
};

#endif