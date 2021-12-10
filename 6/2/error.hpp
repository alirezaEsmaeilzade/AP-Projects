#ifndef __ERROR_H__
#define __ERROR_H__

#include <string>
class Run_time_error : public std::exception{
    public:
        Run_time_error(std::string error_massage);        
        virtual const char* what();
    private:
        std::string error_massage;
};
#endif