#include "Tower.h"
Tower::Tower(Point mouse_position){
    Point convert = find_tower_place(mouse_position);
    cordinat_x = convert.x;
    cordinat_y = convert.y;
    target = NULL;
    tower_shot = NULL;
    range = TOWER_RANGE;
    level = 1;
    image_file = TOWERS_IMAGE_FILE;
    image_format = IMAGES_FORMAT;
}

void Tower::search_in_wave(){
    Enemy* nearst_enemy = NULL;
    double short_distance = MAX_ENEMY_DISTANS;
    for(int i = 0; i < current_wave.size(); i++){
        if(check_distance(current_wave[i]))
            if(short_distance > return_two_point_distance(Point(cordinat_x + SQUER_EDGE / 2 , cordinat_y + SQUER_EDGE / 2), current_wave[i]->get_cordinat()))
                nearst_enemy = current_wave[i];
    }
    if(nearst_enemy != NULL)
        target = nearst_enemy;
    else
        target = NULL;
}

void Tower::guard(std::vector<Enemy*> current_wave){
    set_current_wave(current_wave);
    if(sleep()){
        rate_time += DELAY_PER_SECOND;
        search_in_wave();
        if(target != NULL){
            shoot();
        }
    }
    else
        defense();
}

double Tower::return_two_point_distance(Point first, Point second){
    int delta_x = second.x - first.x;
    int delta_y = second.y - first.y;
    return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

bool Tower::check_rate_time(){
    if(rate_time >= fire_rate){
        rate_time = 0;
        return true;
    }
    return false;
}

void Tower::turn_off(){
    target = NULL;
    delete tower_shot;
    tower_shot = NULL;
}

void Tower::fire(){
    if(target->is_killed()){
        turn_off();
        return;
    }
    if(tower_shot != NULL){
        if(tower_shot->hit_enemy()){
            enjurd_enemy();
            shoot();
        }
        if(tower_shot != NULL)
            tower_shot->move();
    }
    else
        shoot();
}

void Tower::shoot(){
    if(tower_shot != NULL){
        delete tower_shot;
        tower_shot = NULL;
    }
    if((check_rate_time()))
        creat_shot();
}

void Tower::defense(){
    if(check_distance(target) && check_target_is_on_wave()){
        fire();
        rate_time += DELAY_PER_SECOND;
    }
    else
        turn_off();
}

Point Tower::find_tower_place(Point mouse_position){
    Point convert;
    int convert_x = (mouse_position.x - BEG_POINT_X) / SQUER_EDGE;
    int convert_y = (mouse_position.y - BEG_POINT_Y) / SQUER_EDGE;
    convert.x = (convert_x * SQUER_EDGE) + BEG_POINT_X + SQUER_EDGE / 2;
    convert.y = (convert_y * SQUER_EDGE) + BEG_POINT_Y + SQUER_EDGE / 2;
    return convert;
}

bool Tower::check_target_is_on_wave(){
    for(int i = 0; i < current_wave.size(); i++){
        if(target == current_wave[i])
            return true;
    }
    return false;
}

Gatling::Gatling(Point mouse_position) : Tower(mouse_position){
    fire_rate = GATLING_RATE_TIME;
    rate_time = fire_rate;
    damage = GATLING_DAMAGE;
    upgrade_damage = GATLING_UPGRADE_DAMAGE;
    upgrade_cast = GATLING_UPGRADE_CAST;
    image_adress = GATLING_IMAGE_NAME;
}

Missile::Missile(Point mouse_position) : Tower(mouse_position){
    fire_rate = MISSILE_RATE_TIME;
    rate_time = fire_rate;
    damage = MISSILE_DAMAGE;
    upgrade_damage = MISSILE_UPGRADE_DAMAGE;
    upgrade_cast = MISSILE_UPGRADE_CAST;
    image_adress = MISSILE_IMAGE_NAME;
}

void Missile::enjurd_enemy_near_explosion(Point shot_explosion){
    for(int i = 0; i < current_wave.size(); i++){
        if(return_two_point_distance(shot_explosion, current_wave[i]->get_cordinat()) <= MISSILE_EFFECT_SHOT)
            current_wave[i]->decrease_health(damage);
    }
}

Tesla::Tesla(Point mouse_position) : Tower(mouse_position){
    fire_rate = TESLA_RATE_TIME;
    rate_time = fire_rate;
    damage = TESLA_DAMAGE;
    upgrade_damage = TESLA_UPGRADE_DAMAGE;
    upgrade_cast = TESLA_UPGRADE_CAST;
    image_adress = TESLA__IMAGE_NAME;
}

Glue::Glue(Point mouse_position) : Tower(mouse_position){
    fire_rate = GLUE_RATE_TIME;
    rate_time = fire_rate;//
    damage = GLUE_DAMAGE_PERCENT;
    upgrade_damage = GLUE_UPGRADE_DAMAGE_PERCENT;
    upgrade_cast = GLUE_UPGRADE_CAST;
    damage_time_upgrade = GLUE_UPGRADE_DAMAGE_TIME;
    damage_time = GLUE_DAMAGE_TIME;
    image_adress = GLUE_IMAGE_NAME;
}

void Glue::decreas_enemy_near_explosion_speed(Point shot_explosion){
    for(int i = 0; i < current_wave.size(); i++){
        if(return_two_point_distance(shot_explosion, current_wave[i]->get_cordinat()) <= GLUE_EFFECT_SHOT){
            if(!current_wave[i]->are_you_stubborn_enemy()){
                current_wave[i]->decrease_speed_by_glue(damage, damage_time);
            }
        }
    }
}