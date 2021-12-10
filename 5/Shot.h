#ifndef _SHOT_H_
#define _SHOT_H_
#include "RSDL/rsdl.hpp"
#include "Enemy.h"
#include <cmath>
#define SHOT_SPEED 400
#define DELAY_PER_SECOND 0.015
#define SHOT_RADOIS 4
class Shot{
    public:
        Shot(Point cordinate, Enemy* target);
        virtual void draw(Window* window) = 0;
        virtual void enjurd_enemy() = 0;
        bool hit_enemy();
        Point get_place(){return Point(cordinat_x, cordinat_y);}
        void move();
    protected:
        double cordinat_x;
        double cordinat_y;
        int speed;
        Enemy* target;
        bool is_have_blast_wave;
        bool is_have_speed_losser;
        int damage;
};

class Gatling_shot : public Shot{
    public:
        Gatling_shot(Point cordinate, Enemy* target, int damage);
        virtual void draw(Window* window){
            window->fill_circle(Point(cordinat_x, cordinat_y), SHOT_RADOIS, YELLOW);
        }
        virtual void enjurd_enemy(){
            if(hit_enemy()){
                if(!target->are_you_stubborn_enemy()){
                    target->decrease_health(damage);
                }
            }
        }
};

class Missile_shot : public Shot{
    public:
        Missile_shot(Point cordinate, Enemy* target, int damage);
        virtual void draw(Window* window){
            window->fill_circle(Point(cordinat_x, cordinat_y), SHOT_RADOIS, RED);
        }
        virtual void enjurd_enemy(){
            if(hit_enemy()){
                target->decrease_health(damage);
            }
        }
        
};

class Tesla_shot : public Shot{
    public:
        Tesla_shot(Point cordinate, Enemy* target, int damage);
        virtual void enjurd_enemy(){
            if(hit_enemy()){
                target->decrease_health(damage);
            }
        }
        virtual void draw(Window* window){
            window->fill_circle(Point(cordinat_x, cordinat_y), SHOT_RADOIS, BLUE);
        }
};

class Glue_shot : public Shot{
    public:
        Glue_shot(Point cordinate, Enemy* target, int damage, int damage_time);
        virtual void draw(Window* window){
            window->fill_circle(Point(cordinat_x, cordinat_y), SHOT_RADOIS, GREEN);
        }
        virtual void enjurd_enemy(){
            target->decrease_speed_by_glue(damage, damage_time);
        }
    public:
        double damage_time;
};
#endif