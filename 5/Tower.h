#ifndef _TOWER_H_
#define _TOWER_H_
#include "RSDL/rsdl.hpp"
#include "Shot.h"
#include "Enemy.h"
#include <vector>
#define MAX_ENEMY_DISTANS 150
#define TOWER_SIZE 100
#define BEG_POINT_X 122
#define BEG_POINT_Y 174
#define SQUER_EDGE 60
#define GATLING_RATE_TIME 1
#define MISSILE_RATE_TIME 3
#define TESLA_RATE_TIME 1.5
#define GLUE_RATE_TIME 2
#define GATLING_UPGRADE_CAST 40
#define MISSILE_UPGRADE_CAST 60
#define TESLA_UPGRADE_CAST 100
#define GLUE_UPGRADE_CAST 45
#define GATLING_DAMAGE 35
#define MISSILE_DAMAGE 75
#define TESLA_DAMAGE 700
#define GLUE_DAMAGE_TIME 2.5
#define GLUE_DAMAGE_PERCENT 40
#define GATLING_UPGRADE_DAMAGE 35
#define MISSILE_UPGRADE_DAMAGE 75
#define TESLA_UPGRADE_DAMAGE 1000
#define GLUE_UPGRADE_DAMAGE_TIME 0.5
#define GLUE_UPGRADE_DAMAGE_PERCENT 10
#define TOWER_RANGE 150
#define MISSILE_EFFECT_SHOT 50
#define GLUE_EFFECT_SHOT 30
#define TOWERS_IMAGE_FILE "Assets/towers"
#define GATLING_IMAGE_NAME "gattling"
#define MISSILE_IMAGE_NAME "missile"
#define TESLA__IMAGE_NAME "tesla"
#define GLUE_IMAGE_NAME "glue"
#define IMAGES_FORMAT ".png"
class Tower{
    public:
        Tower(Point mouse_position);
        virtual void draw_in_screen(Window* window) = 0;
        bool check_distance(Enemy* target){
            if(return_two_point_distance(Point(cordinat_x + SQUER_EDGE / 2 , cordinat_y + SQUER_EDGE / 2), target->get_cordinat()) <= range)
                return true;
            return false;
        }
        bool is_tower_can_upgrade(int gold){
            return gold > upgrade_cast;
        }
        void guard(std::vector<Enemy*> current_wave);
        void upgrade_tower(){
            level++;
            upgrade_tower_damage();
        }
        int get_tower_upgrade_cast(){return upgrade_cast;}
        bool is_this_point_out_of_your_area(Point a){
            return a.x > cordinat_x + SQUER_EDGE || a.x < cordinat_x || a.y > cordinat_y + SQUER_EDGE || a.y < cordinat_y;
        }
    protected:
        Point find_tower_place(Point mous_position);
        void search_in_wave();
        double return_two_point_distance(Point first, Point second);
        bool sleep(){ return target == NULL; }
        bool check_rate_time();
        void turn_off();
        void fire();
        void shoot();
        virtual void creat_shot() = 0;
        virtual void upgrade_tower_damage() = 0;
        virtual void enjurd_enemy() = 0;
        void defense();
        void set_current_wave(std::vector<Enemy*> wave){
            current_wave = wave;
        }
        bool check_target_is_on_wave();
        float cordinat_x;
        float cordinat_y;
        Shot* tower_shot;
        int upgrade_cast;
        int level;
        int damage;
        double fire_rate;
        int range;
        int upgrade_damage;
        double rate_time;
        Enemy* target;
        std::vector<Enemy*> current_wave;
        std::string image_file;
        std::string image_adress;
        std::string image_format;
};
class Gatling : public Tower{
    public:
        Gatling(Point mouse_position);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_adress + std::to_string(level) + image_format, Rectangle(cordinat_x -  (TOWER_SIZE / 2), cordinat_y - (TOWER_SIZE / 2), TOWER_SIZE, TOWER_SIZE));
            if(tower_shot != NULL)
                tower_shot->draw(window);
        }
        virtual void upgrade_tower_damage(){
            damage += upgrade_damage;
        }
        virtual void creat_shot(){
            Gatling_shot* shot = new Gatling_shot(Point(cordinat_x, cordinat_y), target, damage);
            tower_shot = shot;
        }
        virtual void enjurd_enemy(){
            tower_shot->enjurd_enemy();
        }
};
class Missile : public Tower{
    public:
        Missile(Point mouse_position);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_adress + std::to_string(level) + image_format, Rectangle(cordinat_x - (TOWER_SIZE / 2), cordinat_y - (TOWER_SIZE / 2), TOWER_SIZE, TOWER_SIZE));
            if(tower_shot != NULL)
                tower_shot->draw(window);
        }
        virtual void creat_shot(){
            Missile_shot* shot = new Missile_shot(Point(cordinat_x, cordinat_y), target, damage);
            tower_shot = shot;
        }
        virtual void upgrade_tower_damage(){
            damage += upgrade_damage;
        }
        virtual void enjurd_enemy(){
            enjurd_enemy_near_explosion(tower_shot->get_place());
        }
    private:
        void enjurd_enemy_near_explosion(Point shot_explosion);   
};
class Tesla : public Tower{
    public:
        Tesla(Point mouse_position);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_adress + std::to_string(level) + image_format, Rectangle(cordinat_x - (TOWER_SIZE / 3), cordinat_y - (TOWER_SIZE / 2), TOWER_SIZE / 2, TOWER_SIZE));/////come back
            if(tower_shot != NULL)
                tower_shot->draw(window);
        }
        virtual void creat_shot(){
            Tesla_shot* shot = new Tesla_shot(Point(cordinat_x, cordinat_y), target, damage);
            tower_shot = shot;
        }
        virtual void upgrade_tower_damage(){
            damage += upgrade_damage;
        }
        virtual void enjurd_enemy(){
            tower_shot->enjurd_enemy();
        }
};
class Glue : public Tower{
    public:
        Glue(Point mouse_position);
        virtual void draw_in_screen(Window* window){
            window->draw_img(image_file + "/" + image_adress + std::to_string(level) + image_format, Rectangle(cordinat_x - (TOWER_SIZE / 2), cordinat_y - (TOWER_SIZE / 2), TOWER_SIZE, TOWER_SIZE));
            if(tower_shot != NULL)
                tower_shot->draw(window);
        }
        virtual void creat_shot(){
            Glue_shot* shot = new Glue_shot(Point(cordinat_x, cordinat_y), target, damage, damage_time);
            tower_shot = shot;
        }
        virtual void upgrade_tower_damage(){
            damage += upgrade_damage;
            damage_time += damage_time_upgrade;
        }
        virtual void enjurd_enemy(){
            decreas_enemy_near_explosion_speed(tower_shot->get_place());
        }
    private:
        void decreas_enemy_near_explosion_speed(Point shot_explosion);
        double damage_time;
        double damage_time_upgrade;
};
#endif 
