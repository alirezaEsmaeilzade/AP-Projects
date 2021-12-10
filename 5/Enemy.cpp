#include "Enemy.h"
Enemy::Enemy(std::vector<Point> path, int speed){
    this->path = path;
    this->speed = speed;
    cordinat_x = path[0].x;
    cordinat_y = path[0].y;
    destination = path[1];
    are_you_gluey = false;
    path_index = 1;
    image_file = IMAGE_FILE_NAME;
}
void Enemy::move(){
    if(is_reached_destination()){
        //std::cout<<"reached"<<std::endl;
        cordinat_x = path[path_index].x;
        cordinat_y = path[path_index].y;
        path_index++;
        destination = path[path_index]; 
    }
    double decreas_percent = 0;
    if(check_gluey_shot_effect()){
        decreas_percent = decrease_speed_percent;
        decrease_speed_effect_time -= DELAY_PER_SECOND;
    }
    if(destination.x == cordinat_x){
        if(destination.y > cordinat_y)
            cordinat_y += (1 - decreas_percent / 100) * speed * DELAY_PER_SECOND;
        else
            cordinat_y -= (1 - decreas_percent / 100) * speed * DELAY_PER_SECOND;
    }
    if(destination.y == cordinat_y){
        if(destination.x > cordinat_x)
            cordinat_x += (1 - decreas_percent / 100) * speed * DELAY_PER_SECOND;
        else
            cordinat_x -= (1 - decreas_percent / 100) * speed * DELAY_PER_SECOND;
    }
}
Point Enemy::get_cordinat(){
    Point convert;
    convert.x = cordinat_x;
    convert.y = cordinat_y;
    return convert;
}
void Enemy::decrease_speed_by_glue(double shot_decrease_speed, double shot_effect_time){
    if(!are_you_gluey){
        decrease_speed_percent = shot_decrease_speed;
        decrease_speed_effect_time = shot_effect_time;
        are_you_gluey = true;
    }
}
bool Enemy::check_gluey_shot_effect(){
    if(are_you_gluey){
        if(decrease_speed_effect_time <= 0){
            are_you_gluey = false;
            decrease_speed_effect_time = 0;
            return false;
        }
        return true;
    }
    return false;
}
void Enemy::draw_health(Window* window){
    double health_in_screen = health / initial_health;
    window->fill_rect(Rectangle(cordinat_x - IMAGE_SIZE / 3, cordinat_y - 3 * IMAGE_SIZE / 5, health_in_screen * 2 * IMAGE_SIZE / 3, IMAGE_SIZE / 16), RED);
}
Runner::Runner(std::vector<Point> path, int speed) : Enemy(path, speed){
    initial_health = RUNNER_FIRST_HEALTH;
    kill_reward_for_player = RUNNER_KILL_REWARD;
    kill_player_heart = RUNNER_PLAYER_HEART_KILL;
    are_you_strubborn = false;
    image_name = RUNNER_IMAGE_NAME;
}
Runner_stubborn::Runner_stubborn(std::vector<Point> path, int speed) : Enemy(path, speed){
    initial_health = RUNNER_STUBBORN_FIRST_HEALTH;
    kill_reward_for_player = RUNNER_STUBBORN_KILL_REWARD;
    kill_player_heart = RUNNER_STUBBORN_PLAYER_HEART_KILL;
    are_you_strubborn = true;
    image_name = RUNNER_STUBBORN_IMAGE_NAME;
}
Super_trooper::Super_trooper(std::vector<Point> path, int speed) : Enemy(path, speed){
    initial_health = SUPER_TROOPER_FIRST_HEALTH;
    kill_reward_for_player = SUPER_TROOPER_KILL_REWARD;
    kill_player_heart = SUPER_TROOPER_PLAYER_HEART_KILL;
    are_you_strubborn = false;
    image_name = SUPER_TROOPER_IMAGE_NAME;
}
Scrambler::Scrambler(std::vector<Point> path, int speed) : Enemy(path, speed){
    initial_health = SCRAMBLER_FIRST_HEALTH;
    kill_reward_for_player = SCRAMBLER_KILL_REWARD;
    kill_player_heart = SCRAMBLER_PLAYER_HEART_KILL;
    are_you_strubborn = false;
    image_name = SCRAMBLER_IMAGE_NAME;
}