#ifndef __ERROR_H__
#define __ERROR_H__
#define BAD_REQUEST "Bad Request"
#define LOGINE_ERROR "Permission Denied"
#define EMPTY_DATA "Empty"
#define ROOM_ERROR "Not Enough Room"
#define FOUND_ERROR "Not Found"
#define MONEY_ERROR "Not Enough Credit"
#define RATE_ERROR "NO Rating"
#define INSUFFICIENT_RATING "Insufficient Rating"
#include <string>
class Run_time_error : public std::exception{
    public:
        Run_time_error(std::string error_massage);        
        virtual const char* what();
    private:
        std::string error_massage;
};
class Bad_request : public std::exception{
    public:
        Bad_request();        
        virtual const char* what();
    private:
        std::string error_massage;
};
class Login_error : public std::exception{
    public:
        Login_error();        
        virtual const char* what();
    private:
        std::string error_massage;
};
class Found_error : public std::exception{
    public:
        Found_error();        
        virtual const char* what();
    private:
        std::string error_massage;
};
class Money_error : public std::exception{
    public:
        Money_error();        
        virtual const char* what();
    private:
        std::string error_massage;
};
class Rate_error : public std::exception{
    public:
        Rate_error();        
        virtual const char* what();
    private:
        std::string error_massage;
};
class Insufficient_rating : public std::exception{
    public:
        Insufficient_rating();        
        virtual const char* what();
    private:
        std::string error_massage;

};
class Room_error : public std::exception{
    public:
        Room_error();        
        virtual const char* what();
    private:
        std::string error_massage;

};class Empty_data_error : public std::exception{
    public:
        Empty_data_error();        
        virtual const char* what();
    private:
        std::string error_massage;

};
#endif