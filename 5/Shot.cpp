#include "Shot.h"
Shot::Shot(Point cordinate, Enemy* target){
    cordinat_x = cordinate.x;
    cordinat_y = cordinate.y;
    this->target = target;
    speed = SHOT_SPEED;
}

bool Shot::hit_enemy(){
    Point target_place = target->get_cordinat();
    if((abs((int)cordinat_x - target_place.x) < SHOT_RADOIS) && (abs((int)cordinat_y - target_place.y) < SHOT_RADOIS))
        return true;
    return false;
}

void Shot::move(){
    Point target_place = target->get_cordinat();
    double delta_x = target_place.x - cordinat_x;
    double delta_y = target_place.y - cordinat_y;
    double theta = atan(abs(delta_x / delta_y));
    if(delta_x < 0)
        cordinat_x -= (sin(theta) * speed * DELAY_PER_SECOND);
    else
        cordinat_x += (sin(theta) * speed * DELAY_PER_SECOND);
    if(delta_y < 0)
        cordinat_y -= (cos(theta) * speed * DELAY_PER_SECOND);
    else
        cordinat_y += (cos(theta) * speed * DELAY_PER_SECOND);
}

Gatling_shot::Gatling_shot(Point cordinate, Enemy* target, int damage) : Shot(cordinate, target){
    speed = SHOT_SPEED;
    this->damage = damage;
}

Missile_shot::Missile_shot(Point cordinate, Enemy* target, int damage) : Shot(cordinate, target){
    speed = SHOT_SPEED;
    this->damage = damage;
}

Tesla_shot::Tesla_shot(Point cordinate, Enemy* target, int damage) : Shot(cordinate, target){
    speed = SHOT_SPEED;
    this->damage = damage;
}

Glue_shot::Glue_shot(Point cordinate, Enemy* target, int damage, int damage_time) : Shot(cordinate, target){
    speed = SHOT_SPEED;
    this->damage = damage;
    this->damage_time = damage_time;
}        