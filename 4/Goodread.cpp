#include "Goodread.h"

bool compare_book_by_id(Book a, Book b){ return (a.get_id() < b.get_id()); }
bool compare_book_by_special_rate(Book a, Book b){ return (a.get_average_of_special_rating() < b.get_average_of_special_rating()); }
Author* Good_read::find_book_author_by_id(int id){
    for(int i = 0; i < authors.size(); i++){
        if(authors[i].is_id_correct(id)){
            return &authors[i];
        }
    }
}
void Good_read::initialize_book(std::vector< std::string> input){
    for(std::string save : input){
        std::vector<std::string> splited_part = split_string(save, separator_one);
        int id = stoi(splited_part[0]);
        std::string title = splited_part[1];
        Author* book_auther= find_book_author_by_id(stoi(splited_part[2]));
        std::string genre = splited_part[3];
        Book convert(id, title, book_auther, genre);
        books.push_back(convert);
    }
}
Book* Good_read::find_book_by_id(int id){
    for(int i = 0; i < books.size(); i++){
        if(books[i].is_id_true(id))
            return &books[i];
    }
}
void Good_read::initialize_user(std::vector<std::string> input){
    for(std::string save : input){
        std::vector<std::string> splited_part = split_string(save, separator_one);
        int id = stoi(splited_part[0]);
        std::string name = splited_part[1];
        std::string place_of_birth = splited_part[2];
        std::string member_since = splited_part[3];
        std::vector<std::string> favorite_genre = split_string(splited_part[5], separator_two);
        User convert(id, name, place_of_birth, member_since, favorite_genre);
        std::vector<std::string> favorite_authors_id = split_string(splited_part[4], separator_two);
        std::vector<std::string> want_read = split_string(splited_part[6], separator_two);
        std::vector<std::string> curr_read = split_string(splited_part[7], separator_two);
        std::vector<std::string> read = split_string(splited_part[8], separator_two);
        for(std::string find : favorite_authors_id)
            convert.add_author(find_book_author_by_id(stoi(find)));
        for(std::string for_push : want_read)
            convert.add_shelf_info(find_book_by_id(stoi(for_push)), "want_to_read");
        for(std::string for_push : curr_read)
            convert.add_shelf_info(find_book_by_id(stoi(for_push)), "currently_reading");
        for(std::string for_push : read)
            convert.add_shelf_info(find_book_by_id(stoi(for_push)), "read");
        users.push_back(convert);
    }
}
User* Good_read::find_user_by_id(int id){
    for(int i = 0; i < users.size(); i++){
        if(users[i].is_id_correct(id))
            return &users[i];
    }
}
void Good_read::initialize_review(std::vector<std::string> input){
    for(std::string save : input){
        std::vector<std::string> splited_part = split_string(save, separator_one);
        int id = stoi(splited_part[0]);
        Book* book_id = find_book_by_id(stoi(splited_part[1]));
        User* user_id = find_user_by_id(stoi(splited_part[2]));
        int rating = stoi(splited_part[3]);
        std::string date = splited_part[4];
        int number_of_like= stoi(splited_part[5]);
        Review convert(id, book_id, user_id, rating, date, number_of_like);
        reviews.push_back(convert);
    }
}
void Good_read::initialize_follow(std::vector< std::string> input){
    for(int i = 0; i < input.size(); i++){
        std::vector< std::string> splited_part = split_string(input[i], separator_one);
        User* init_user_follow = find_user_by_id(stoi(splited_part[0]));
        if(!splited_part[1].empty()){
            std::vector< std::string> splited_parts = split_string(splited_part[1], separator_two);
            for(int i = 0; i < splited_parts.size(); i++)
                init_user_follow->set_followings(find_user_by_id(stoi(splited_parts[i])));
        }
        if(!splited_part[2].empty()){
            std::vector< std::string> splited_parts = split_string(splited_part[2], separator_two);
            for(int i = 0; i < splited_parts.size(); i++)
                init_user_follow->set_followers(find_user_by_id(stoi(splited_parts[i])));
        }
    }
}
void Good_read::initialize_all(std::vector<std::vector <std::string> > input){
    for(std::string save : input[0]){
        Author convert(save);
        authors.push_back(convert);
    }
    initialize_book(input[1]);
    initialize_user(input[2]);
    initialize_review(input[3]);
    initialize_follow(input[4]);
}
void Good_read::initialize_books_rate(){
    for(int i = 0; i < reviews.size(); i++)
        reviews[i].add_rate_to_book_rating();
}
void Good_read::initialize_books_special_rate(){
    for(int i = 0; i < reviews.size(); i++)
        reviews[i].add_special_rate_to_book();
}
void Good_read::initialize_books_special_rate_average(){
    for(int i = 0; i < books.size(); i++)
        books[i].set_average_of_special_rating();
}
std::vector <std::string> Good_read::read_from_file(std::string file_name){
    std::string head_of_table;
    std::vector <std::string> input_file_lines;
    std::ifstream input_file;
    input_file.open(file_name);
    getline(input_file, head_of_table);
    while(!input_file.eof()){
        std::string one_line_of_file;
        getline(input_file,one_line_of_file);
        if(!one_line_of_file.empty())
            input_file_lines.push_back(one_line_of_file);
    }
    return input_file_lines; 
}
void Good_read::find_best_book(){
    Book best = books[0];
    float max = 0;
    for(int i = 0; i < books.size(); i++){
        if(max < books[i].get_average_of_rateing()){
            best = books[i];
            max = books[i].get_average_of_rateing();
        }
    }
    best.print_book_info();
}
void Good_read::show_author_info(int author_id){
    for(Author find_for_show : authors){
        if(find_for_show.is_id_correct(author_id))
            find_for_show.print();
    }
    std::cout<< "Books:" << std::endl;
    for(Book find_for_show : books){
        if(find_for_show.is_author_id_true(author_id))
            find_for_show.print_book_info_for_author();   
    }
}
void Good_read::show_user_shelf(int user_id, std::string shelf_type, std::string genre){
    for(User find : users){
        if(find.is_id_correct(user_id)){
            find.show_shelf_of_user(shelf_type, genre);
            return;    
        }
    }
}
void Good_read::comput_user_credit(int user_index){
    int number_of_user_reviews_likes = 0;
    int number_of_likes = 0;
    int number_of_user_reviews = 0;
    for(Review comput_credit : reviews){
        if(comput_credit.is_id_for_this_user(users[user_index].get_id())){
            comput_credit.add_user_likes_number();
            number_of_user_reviews++;
            int likes_num = comput_credit.get_number_of_like();
            number_of_user_reviews_likes += likes_num;
            number_of_likes += likes_num;
        }
        else{
            number_of_likes += comput_credit.get_number_of_like();
        }
    }
    double credit = (((double)number_of_user_reviews_likes / (double)number_of_likes) + ((double)number_of_user_reviews / (double)reviews.size())) / 2;
    users[user_index].set_credit(credit);
}
void Good_read::comput_all_user_credit(){
    for(int i = 0; i < users.size(); i++)
        comput_user_credit(i);
}
void Good_read::show_user_credit(int user_id){
    for(int i = 0; i < users.size(); i++){
        if(users[i].is_id_correct(user_id))
            std::cout<< std::fixed << std::setprecision(6) << users[i].get_credit() << std::endl;
    }
}
void Good_read::find_best_user(){
    int max_like = 0;
    User best_user = users[0];
    for(int i = 0; i < users.size(); i++){
        if(max_like < users[i].get_like_numbers()){
            max_like = users[i].get_like_numbers();
            best_user = users[i];
        }
    }
    best_user.print();
}
void Good_read::print_books_review(int book_id){
    std::cout<< "Reviews:" << std::endl;
    for(int i = 0; i < reviews.size(); i++){
        if(reviews[i].is_id_for_this_book(book_id))
            reviews[i].print();
    }
}
void Good_read::suggest_first_book(int id){
    User* user = find_user_by_id(id);
    float max = 0;
    Book sugg_book = books[0];
    for(int i = 0; i < books.size(); i++){
        if(max < books[i].comput_score(user->get_favorite_genre())){
            max = books[i].comput_score(user->get_favorite_genre());
            sugg_book = books[i];
        }
    }
    sugg_book.print_book_for_suggest();
    print_books_review(sugg_book.get_id());
}
std::vector<Book> Good_read::get_tree_book_of_user(User* user){
    std::vector<Book*> read_book_of_user = user->get_read_book_of_shelf();
    int number_of_suggest_book;
    std::vector<Book> check_read_book;
    for(int i = 0; i < read_book_of_user.size(); i++)
        check_read_book.push_back(*read_book_of_user[i]);
    sort(check_read_book.begin(), check_read_book.end(), compare_book_by_special_rate);
    if(number_of_suggest_followings_book > read_book_of_user.size())
        number_of_suggest_book = read_book_of_user.size();
    else
        number_of_suggest_book = number_of_suggest_followings_book;
    std::vector<Book> suggest_book;
    for(int i = check_read_book.size() - 1; i > check_read_book.size() - number_of_suggest_book - 1; i--)
        suggest_book.push_back(check_read_book[i]);
    return suggest_book;      
}

bool Good_read::check_duplicated(User* user, std::vector<User*> users){
    for(int i = 0; i < users.size(); i++){
        if(users[i] == user)
            return false;
    }
    return true;
}
void Good_read::find_follow(User* user, std::vector<User*> &following){
    std::vector<User*> unchecked_following = user->get_followings();
    if(!unchecked_following.empty()){
        for(int i = 0; i < unchecked_following.size(); i++){
            if(check_duplicated(unchecked_following[i], following)){
                following.push_back(unchecked_following[i]);
                find_follow(unchecked_following[i], following);
            }
        }
    }
    return;
}
Book Good_read::find_book_with_most_reapid(std::vector<Book> for_counting){
    sort(for_counting.begin(), for_counting.end(), compare_book_by_id);
    Book find_most_reapid = for_counting[0];
    Book curr_book = for_counting[0];
    int count = 0, max = 0;
    for(int i = 0; i < for_counting.size(); i++){
        if(curr_book.is_id_true(for_counting[i].get_id())){
            count++;
        }
        else{
            if(count > max){
                max = count;
                find_most_reapid = curr_book;
            }
            curr_book = for_counting[i];
            count = 1;
        }
    }
    return find_most_reapid;
}
void Good_read::delete_user_from_followings(std::vector<User*> &following_of_user, int id){
    for(int i = 0; i < following_of_user.size(); i++){
        if(following_of_user[i]->is_id_correct(id))
            following_of_user.erase(following_of_user.begin() + i);
    }
}
std::vector<Book> Good_read::make_favorite_book_of_following(std::vector<User*> following_of_user){
    std::vector<Book> for_counting;
    for(int i = 0; i < following_of_user.size(); i++){
        std::vector<Book> find = get_tree_book_of_user(following_of_user[i]);
        for_counting.insert(for_counting.end(), find.begin(), find.end());
    }
    return for_counting;
}
void Good_read::suggest_second_book(int user_id){
    std::vector<User*> following_of_user;
    find_follow(find_user_by_id(user_id), following_of_user);
    delete_user_from_followings(following_of_user, user_id);
    std::vector<Book> for_counting = make_favorite_book_of_following(following_of_user);
    Book suggest = find_book_with_most_reapid(for_counting);
    suggest.print_book_for_suggest();
    print_books_review(suggest.get_id());
}
