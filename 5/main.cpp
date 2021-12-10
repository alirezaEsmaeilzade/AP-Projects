#include "RSDL/rsdl.hpp"
#include "Player.h"
#include "Screen.h"
using namespace std;
#define SCREEN_WIDTH 1356
#define SCREEN_HEIGHT 1024
#define GATTING 1
#define MISSILE 2
#define TESLA 3
#define GLUE 4
#define DELAY_PER_SECOND 0.015
#define GATTING_KEY 'g'
#define MISSILE_KEY 'm'
#define TESLA_KEY 't'
#define GLUE_KEY 'l'
#define UPGRADE_KEY 'u'

void update(Window* window, Player* player, Screen* screen_control){
	Point mouse_position;
    screen_control->update();
    if(!player->is_play_ended()){ 
    player->upadat();
        while(window->has_pending_event()){
            Event e = window->poll_for_event();
            switch(e.get_type()){
	    		case Event::EventType::QUIT:
	    			exit(0);
	    			break;
	    		case Event::EventType::LCLICK:{
                    mouse_position = e.get_mouse_position();
                    screen_control->set_mouse_point(mouse_position);
                    break;
                }
                case Event::EventType::KEY_PRESS:{
                    switch(e.get_pressed_key()){
                        case GATTING_KEY:{
                            player->set_new_tower(GATTING, screen_control);
                            break;
                        }
                        case MISSILE_KEY:{
                            player->set_new_tower(MISSILE, screen_control);
                            break;
                        }
                        case TESLA_KEY:{
                            player->set_new_tower(TESLA, screen_control);
                            break;
                        }
                        case GLUE_KEY:{
                            player->set_new_tower(GLUE, screen_control);
                            break;
                        }
                        case UPGRADE_KEY:{
                            player->upgrade_tower(screen_control->get_mouse_point());
                            break;
                        }
                        default:{
                            screen_control->record_error(WRONG_KEY);
                            break;
                        }
                    }
                }
	    	}
        }
    }
    else{
        if(window->has_pending_event()){
            Event e = window->poll_for_event();
            if(e.get_type() == Event::EventType::QUIT){
                player->clean();
                exit(0);
            }
        }
    }
}

void draw(Window* window, Player* player, Screen* screen_controler){
    window->clear();
    window->draw_img("Assets/background.png");
    screen_controler->draw(window);
    player->draw(window);
    window->update_screen();
}

int main(int argc, char* argv[]){
    Player player(argv[1]);
    Screen screen_controler;
    Window *window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "FeildRunners");
	while(true) {
		update(window, &player, &screen_controler);
		draw(window, &player, &screen_controler);
		delay(DELAY_PER_SECOND * 1000);
	}
}