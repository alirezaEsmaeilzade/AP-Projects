#include "functions.h"
#include "Book.h"
#include "User.h"
#include <string>
#include <iostream>
#include <vector>

class Review{
    public:
        Review(int id, Book* book_of_review, User* reviewer_user, int rating, std::string date, int number_of_like){
            this->id = id;
            this->book_review = book_of_review;
            this->reviewer_user = reviewer_user;
            this->rating = rating;
            this->date = date;
            this->number_of_like= number_of_like;
        }
        void add_rate_to_book_rating(){
            book_review->add_sum_rate(rating);
        }
        void add_special_rate_to_book(){
            float one_s_rate = reviewer_user->get_credit() * rating;
            book_review->add_sum_special_rate(one_s_rate);
        }
        double books_ave(){
            book_review->get_average_of_rateing();
        }
        int get_number_of_like(){return number_of_like;}
        bool is_id_for_this_user(int user_id){
            if(reviewer_user->is_id_correct(user_id))
                return true;
            return false;
        }
        bool is_id_for_this_book(int book_id){
            if(book_review->is_id_true(book_id))
                return true;
            return false;
        }
        void add_user_likes_number(){
            reviewer_user->add_sum_likes_number(number_of_like);
        }
        int get_all_users_like_num(){
            return reviewer_user->get_like_numbers();
        }
        void print_book_info(){
            book_review->print_book_info();
        }
        void print_user_info(){
            reviewer_user->print();
        }
        void print();
    private:
        int id;
        Book* book_review;
        User* reviewer_user;
        int rating;
        std::string date;
        int number_of_like;
};
