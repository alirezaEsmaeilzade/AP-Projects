#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "RSDL/rsdl.hpp"
#include <vector>
#include <cmath>
#define DELAY_PER_SECOND 0.015
#define RUNNER_FIRST_HEALTH 250
#define RUNNER_STUBBORN_FIRST_HEALTH 400
#define SUPER_TROOPER_FIRST_HEALTH 500
#define SCRAMBLER_FIRST_HEALTH 100
#define RUNNER_SPEED 50
#define RUNNER_STUBBORN_SPEED 30
#define SUPER_TROOPER_SPEED 25
#define SCRAMBLER_SPEED 90
#define RUNNER_PLAYER_HEART_KILL 1
#define RUNNER_STUBBORN_PLAYER_HEART_KILL 4
#define SUPER_TROOPER_PLAYER_HEART_KILL 4
#define SCRAMBLER_PLAYER_HEART_KILL 2
#define RUNNER_KILL_REWARD 6 
#define RUNNER_STUBBORN_KILL_REWARD 10
#define SUPER_TROOPER_KILL_REWARD 8
#define SCRAMBLER_KILL_REWARD 4
#define INCREAS_PERCENT 0.1
#define IMAGE_SIZE 70
#define IMAGE_FILE_NAME "Assets/enemies"
#define RUNNER_IMAGE_NAME "runner.png"
#define RUNNER_STUBBORN_IMAGE_NAME "stubborn-runner.png"
#define SUPER_TROOPER_IMAGE_NAME "supertrooper.png"
#define SCRAMBLER_IMAGE_NAME "scrambler.png"
class Enemy{
    public:
        Enemy(std::vector<Point> path, int speed);
        void set_round(int round){this->round = round;}
        void increas_health_by_round(){
            health = (0.9 + INCREAS_PERCENT * round) * initial_health;
        }
        virtual void draw_in_screen(Window* window) = 0;
        bool are_you_stubborn_enemy(){return are_you_strubborn;}
        int get_heart(){return kill_player_heart;}
        bool is_reached_finish_line(){
            if((abs(cordinat_x - path[path.size() - 1].x) <= 1) && (abs(cordinat_y - path[path.size() - 1].y) <= 1)){
                return true;
            }
            return false;
        }
        bool is_killed(){return health <= 0;}
        Point get_cordinat();
        void decrease_health(int shot_damage){ 
            if(health > shot_damage)
                health -= shot_damage;
            else
                health = 0;
        }
        void decrease_speed_by_glue(double shot_decrease_speed, double shot_effect_time);
        int spend_gold_to_player(){return kill_reward_for_player;}
        void move();
        void draw_health(Window* window);
    protected:
        bool is_reached_destination(){
            if((abs(cordinat_x - destination.x) <= 1) && (abs(cordinat_y - destination.y) <= 1)){
                return true;
            }
            return false;
        }
        bool check_gluey_shot_effect();
        std::vector<Point> path;
        float cordinat_x;
        float cordinat_y;
        Point destination;
        int speed;
        int path_index;
        double health;
        int initial_health;
        int kill_player_heart;
        int kill_reward_for_player;
        bool are_you_strubborn;
        bool are_you_gluey;
        double decrease_speed_percent;
        double decrease_speed_effect_time;
        int round;
        std::string image_file;
        std::string image_name;
};

class Runner : public Enemy{
    public:
        Runner(std::vector<Point> path, int speed);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_name, Rectangle(cordinat_x - IMAGE_SIZE / 2, cordinat_y - IMAGE_SIZE / 2, IMAGE_SIZE, IMAGE_SIZE));
            draw_health(window);
        }
};

class Runner_stubborn : public Enemy{
    public:
        Runner_stubborn(std::vector<Point> path, int speed);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_name, Rectangle(cordinat_x - IMAGE_SIZE / 2, cordinat_y - IMAGE_SIZE / 2, IMAGE_SIZE, IMAGE_SIZE));
            draw_health(window);
        }
};
class Super_trooper : public Enemy{
    public:
        Super_trooper(std::vector<Point> path, int speed);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_name, Rectangle(cordinat_x - IMAGE_SIZE / 2, cordinat_y - IMAGE_SIZE / 2, IMAGE_SIZE, IMAGE_SIZE));
            draw_health(window);
        }  
};

class Scrambler : public Enemy{
    public:
        Scrambler(std::vector<Point> path, int speed);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_name, Rectangle(cordinat_x - IMAGE_SIZE / 2, cordinat_y - IMAGE_SIZE / 2, IMAGE_SIZE, IMAGE_SIZE));
            draw_health(window);
        }
};

#endif