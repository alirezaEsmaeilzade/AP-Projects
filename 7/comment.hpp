#ifndef __COMMENT_H__
#define __COMMENT_H__
#include "user.hpp"
#include <string>
#include <iostream>
class Comment{
    public:
        Comment(User* user, std::string comment);
        void print();
    private:
        std::string comment;
        User* user;
};
#endif