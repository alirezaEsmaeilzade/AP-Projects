#include "comment.hpp"
Comment::Comment(User* user, std::string comment){
    this->user = user;
    this->comment = comment;
}

void Comment::print(){
    user->print_username_for_comment();
    std::cout << comment << std::endl;
}