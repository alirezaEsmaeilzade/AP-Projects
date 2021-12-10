#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "RSDL/rsdl.hpp"
#include "Enemy.h"
#include "Tower.h"
#include "Screen.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#define TOWER_SIZE 100
#define BEG_POINT_X 122
#define BEG_POINT_Y 174
#define SQUER_EDGE 60
#define BEG_MONEY 200
#define BEG_HEART 20
#define RUNNER_SPEED 50
#define RUNNER_STUBBORN_SPEED 30
#define SUPER_TROOPER_SPEED 25
#define SCRAMBLER_SPEED 90
#define GATTING 1
#define MISSILE 2
#define TESLA 3
#define GLUE 4
#define GATLING_CAST 55
#define MISSILE_CAST 70
#define TESLA_CAST 120
#define GLUE_CAST 60
#define DELAY_PER_SECOND 0.015
#define DELAY_TIME_FOR_WAVE 3
#define DELAY_TIME_FOR_EACH_ENEMY 0.5
#define FONT "OpenSans.ttf"
#define FILE_NAME "Assets"
#define WIN_PHRASE "you win"
#define LOSS_PHRASE "you loss"
#define HEAD_FONT_SIZE 24
#define RESULT_FONT_SIZE 60
class Player{
    public:
        Player(std::string file_name);
        void set_new_tower(int tower_name, Screen* Screen_controler);
        void upgrade_tower(Point mouse_position);
        void draw(Window* window);
        void upadat();
        bool is_play_ended();
        void clean();
    private:
        std::vector<std::string> read_from_file(std::string file_name);
        std::vector<Point> convert_int_cordinat_to_point(std::vector<int> path_int_cordinat);
        std::vector<int> return_number_of_each_line(std::string input);
        std::vector<int> make_path_cordinat_sequens(std::vector<int> path_int_cordinat);
        std::vector<Enemy*> make_enemys(std::vector<int> number_of_enemys);
        void inititialize_all_enemy(std::vector<std::string> line_of_file);
        bool check_is_duplicat(Point place);
        bool check_is_on_the_path(Point place);
        bool check_place(Point place);
        bool can_build_tower(int tower_name, Screen* Screen_controler);
        void enemy_wave_controler();
        void add_random_enemy_in_wave();
        bool whats_is_play_result();
        bool time_controler();
        bool control_gap_time_between_enemys();
        void delete_reached_enemys();
        void delete_killed_enemys();
        void round_controler();
        Enemy* search_enemy_for_tower(Tower* tower);
        void draw_path(Window* window){
            for(int i = 0; i < path.size(); i++)
                window->fill_circle(path[i], 0.1 * SQUER_EDGE, GREEN);
        }
        std::vector<Point> path;
        std::vector<std::vector< Enemy*> > enemys;
        std::vector<Enemy*> current_wave;
        std::vector<Enemy*> lineup_enemy;
        std::vector<Tower*> towers;
        int heart;
        int money;
        int round;
        double time_round;
        double gap_time_between_enemys;
};
#endif