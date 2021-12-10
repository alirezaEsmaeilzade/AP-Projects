#include "Screen.h"
void Screen::show_error(Window* window){
    std::string error_massage;
    switch(error_type){
        case WRONG_KEY:{
            error_massage = "you press wrong key! press g, m, t, l or u";
            break;
        }
        case WRONG_OUT_OF_FIELD:{
            error_massage = "you can't choice place out of field for build tower";
            break;
        }
        case WRONG_IN_PATH:{
            error_massage = "you can't choice place in path for build tower";
            break;
        }
        case WRONG_DUPLICAT_TOWER:{
            error_massage = "in this place build tower already choice again";
            break;
        }
        case WRONG_TOWER_CAST:{
            error_massage = "you choice tower expensive than your gold";
            break;
        }
        default:{
            break;
        }
    }
    window->show_text(error_massage, Point(450, 100), RED, "Assets/OpenSans.ttf");
}