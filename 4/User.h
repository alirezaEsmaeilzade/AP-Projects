#ifndef _USER_H_
#define _USER_H_
#include "Author.h"
#include "Book.h"
#include "functions.h"
#include "Shelf.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

bool compare_by_id(Author a, Author b);

class User{
    public:
        User(int id, std::string name, std::string place_of_birth, std::string member_since,  std::vector<std::string> favorite_genre, int number_of_like = 0){
            this->id = id;
            this->name = name;
            this->place_of_birth = place_of_birth;
            this->member_since = member_since;
            this->favorite_genre = favorite_genre;
            this->number_of_like = number_of_like;
            credit = 0;
        }
        bool is_id_correct(int id);
        void add_author(Author* favorite_authors_member){
            favorite_authors.push_back(favorite_authors_member);
        }
        void add_shelf_info(Book* shelf_info, std::string shelf_type){
            if(shelf_type == "read")
                shelf.add_read(shelf_info);
            else if(shelf_type == "currently_reading")
                shelf.add_currently_read(shelf_info);
            else
                shelf.add_want_to_read(shelf_info);
        }
        void show_shelf_of_user(std::string shelf_type, std::string genre){
            shelf.show_sorted_shelf(shelf_type, genre);
        }
        void add_sum_likes_number(int likes_num){
            number_of_like += likes_num;
        }
        void set_followings(User* following){
            followings.push_back(following);
        }
        void set_followers(User* follower){
            followers.push_back(follower);
        }
        std::vector<User*> get_followings(){return followings;}
        std::vector<User*> get_followers(){return followers;}
        std::vector<std::string> get_favorite_genre(){return favorite_genre;}
        int get_like_numbers(){return number_of_like;}
        double get_credit(){return credit;}
        void set_credit(double new_credit){credit = new_credit;}
        int get_id(){return id;}
        std::vector<Book*> get_read_book_of_shelf(){return shelf.get_read();}
        void print();
    private:
        void print_favorite_author();

        int id;
        std::string name;
        std::string place_of_birth;
        std::string member_since;
        std::vector <Author*> favorite_authors;
        std::vector <std::string> favorite_genre;
        Shelf shelf;
        int number_of_like;
        double credit;
        std::vector<User*> followings;
        std::vector<User*> followers; 
};
#endif