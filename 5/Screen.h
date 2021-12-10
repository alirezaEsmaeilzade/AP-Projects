#ifndef _SCREEN_H_
#define _SCREEN_H_
#include "RSDL/rsdl.hpp"
#define WRONG_KEY 1
#define WRONG_OUT_OF_FIELD 2
#define WRONG_IN_PATH 3
#define WRONG_DUPLICAT_TOWER 4
#define WRONG_TOWER_CAST 5
#define DELAY_PER_SECOND 0.015
class Screen{
    public:
        Screen(){
            show_time = 2;
            error_type = 0;
        }
        void set_mouse_point(Point mouse){
            select = mouse;
        }
        Point get_mouse_point(){return select;}
        void update(){
            if(error_type != 0){
                collect();
            }
        }
        void record_error(int error_type){
            this->error_type = error_type;
            time = 0;
        }
        void draw(Window* window){
            if(error_type != 0){
                if(check_time()){
                    show_error(window);
                }
            }
        }
    private:
        void collect(){time += DELAY_PER_SECOND;}
        bool check_time(){
            if(time <= show_time){
                return true;
            }
            return false;
        }
        void show_error(Window* window);
        Point select;
        double show_time; 
        double time;
        int error_type;
};

#endif