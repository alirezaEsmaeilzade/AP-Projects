#include "functions.h"
#include "Book.h"
#include "Review.h"
#include "User.h"
#include "Author.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

#define separator_one ','
#define separator_two '$'
#define number_of_file 5
#define number_of_suggest_followings_book 3

bool compare_book_by_special_rate(Book a, Book b);
bool compare_book_by_id(Book a, Book b);

class Good_read{
public:
    Good_read(std::string folder_name){
        std::vector<std::vector<std::string> > line_of_all_file (number_of_file);
        line_of_all_file[0] = read_from_file("./" + folder_name + "/authors.csv");
        line_of_all_file[1] = read_from_file("./" + folder_name + "/books.csv");
        line_of_all_file[2] = read_from_file("./" + folder_name + "/users.csv");
        line_of_all_file[3] = read_from_file("./" + folder_name + "/reviews.csv");
        line_of_all_file[4] = read_from_file("./" + folder_name + "/follow_edges.csv");
        initialize_all(line_of_all_file);
        comput_all_user_credit();
        initialize_books_rate();
        initialize_books_special_rate();
        initialize_books_special_rate_average();
    }
    void show_author_info(int author_id);
    void show_user_shelf(int user_id, std::string shelf_type, std::string genre);
    void show_user_credit(int user_id);
    void find_best_book();
    void find_best_user();
    void suggest_first_book(int id);
    void suggest_second_book(int id);
private:
    Author* find_book_author_by_id(int id);
    void initialize_book(std::vector< std::string> input);
    Book* find_book_by_id(int id);
    void initialize_user(std::vector<std::string> input);
    User* find_user_by_id(int id);
    void initialize_review(std::vector<std::string> input);
    void initialize_follow(std::vector< std::string> input);
    void initialize_all(std::vector<std::vector <std::string> > input);
    void initialize_books_rate();
    void initialize_books_special_rate();
    void initialize_books_special_rate_average();
    std::vector <std::string> read_from_file(std::string file_name);
    void comput_user_credit(int user_id);
    void comput_all_user_credit();
    std::vector<Book> get_tree_book_of_user(User* user);
    bool check_duplicated(User* user, std::vector<User*> users);
    Book find_book_with_most_reapid(std::vector<Book> for_counting);
    void print_books_review(int book_id);
    void delete_user_from_followings(std::vector<User*> &following_of_user, int id);
    std::vector<Book> make_favorite_book_of_following(std::vector<User*> following_of_user);
    void find_follow(User* user, std::vector<User*> &following);

    std::vector<Book> books;
    std::vector<User> users;
    std::vector<Author> authors;
    std::vector<Review> reviews;
};
