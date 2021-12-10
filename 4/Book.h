#ifndef _BOOk_H_
#define _BOOk_H_
#include "functions.h"
#include "Author.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

class Book{
    public:
        Book(int id, std::string title, Author* author_id, std::string genre, int sum_all_rating = 0, int number_of_review = 0, double sum_special_rating = 0){
            this->id = id;
            this->title = title;
            author_of_book = author_id;
            this->genre = genre;
            this->sum_all_rating = sum_all_rating;
            this->number_of_review = number_of_review;
            this->sum_special_rating = sum_special_rating;
        }
        void add_sum_rate(int rate){
            sum_all_rating += rate;
            number_of_review++;
        }
        void add_sum_special_rate(double special_rate){
            sum_special_rating += special_rate;
        }
        int get_id(){return id;}
        std::string get_title(){return title;}
        double comput_score(std::vector <std::string> favorite_genre);
        double get_average_of_rateing(){
            if(number_of_review != 0)
                return (double)sum_all_rating / (double)number_of_review;
            return 0;
        }
        bool is_author_id_true(int id);
        bool is_id_true(int id);
        bool is_genre_true(std::string unchecked_genre);
        void print_book_info_for_author();
        void print_book_for_shelf();
        void print_book_info();
        void print_book_for_suggest();
        void set_average_of_special_rating(){
            if(number_of_review != 0)
                average_of_special_rate = (double)sum_special_rating / (double)number_of_review;
            else
                average_of_special_rate = 0;
        }
        double get_average_of_special_rating(){return average_of_special_rate;}
    private:
        int id;
        std::string title;
        Author* author_of_book;
        std::string genre;
        int sum_all_rating;
        int number_of_review;
        double sum_special_rating;
        double average_of_special_rate;
};
#endif