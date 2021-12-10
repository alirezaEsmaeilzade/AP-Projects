#include "Player.h"
Player::Player(std::string file_name){
    heart = BEG_HEART;
    money = BEG_MONEY;
    round = 1;
    time_round = 0;
    gap_time_between_enemys = 0;
    std::vector<std::string> line_of_file = read_from_file(file_name);
    path = convert_int_cordinat_to_point(make_path_cordinat_sequens(return_number_of_each_line(line_of_file[0])));
    inititialize_all_enemy(line_of_file);
}

std::vector<int> Player::return_number_of_each_line(std::string input){
    std::vector<int> path_cordinat;
    std::stringstream ss(input);
    while(ss.good()){
        std::string substr;
        std::getline(ss, substr, ' ');
        path_cordinat.push_back(stoi(substr));
    }
    return path_cordinat;
}

std::vector<int> Player::make_path_cordinat_sequens(std::vector<int> path_int_cordinat){
    std::vector<int> change;
    int pervois_cordinat_x = path_int_cordinat[0];
    int pervois_cordinat_y = path_int_cordinat[1];
    change.push_back(pervois_cordinat_x);
    change.push_back(pervois_cordinat_y);
    for(int i = 2; i < path_int_cordinat.size(); i += 2){
        std::vector<int> bein;
        if(pervois_cordinat_x == path_int_cordinat[i]){
            int khala = path_int_cordinat[i + 1] - pervois_cordinat_y;
            if(khala != 0){
                if(khala > 0){
                    for(int j = 1; j < khala; j++){
                        bein.push_back(pervois_cordinat_x);
                        bein.push_back(pervois_cordinat_y + j);
                    }
                }
                else{
                    for(int j = 1; j < abs(khala); j++ ){
                        bein.push_back(pervois_cordinat_x);
                        bein.push_back(pervois_cordinat_y - j);
                    }
                }
            }
        }
        else{
            int khala = path_int_cordinat[i] - pervois_cordinat_x;
            if(khala != 0){
                if(khala > 0){
                    for(int j = 1; j < khala; j++){
                        bein.push_back(pervois_cordinat_x + j);
                        bein.push_back(pervois_cordinat_y);
                    }
                }
                else{
                    for(int j = 1; j < abs(khala); j++){
                        bein.push_back(pervois_cordinat_x - j);
                        bein.push_back(pervois_cordinat_y);
                    }
                }
            }
        }
    change.insert(change.end(), bein.begin(), bein.end());
    change.push_back(path_int_cordinat[i]);
    change.push_back(path_int_cordinat[i + 1]); 
    pervois_cordinat_x = path_int_cordinat[i];
    pervois_cordinat_y = path_int_cordinat[i + 1];
    }
    return change;
}

std::vector<std::string> Player::read_from_file(std::string file_name){
    std::ifstream input_file;
    input_file.open(file_name);
    std::vector<std::string> line_of_file;
    if(!input_file.is_open()){
        std::cout<<"file is not in diractry.\n";
        abort();
    }
    while(!input_file.eof()){
        std::string one_line;
        std::getline(input_file, one_line, '\n');
        if(!one_line.empty())
            line_of_file.push_back(one_line);
    }
    return line_of_file;
}

std::vector<Point> Player::convert_int_cordinat_to_point(std::vector<int> path_int_cordinat){
    std::vector<Point> path_points;
    for(int i = 0; i < path_int_cordinat.size(); i += 2){
        Point convert;
        convert.x = BEG_POINT_X + (SQUER_EDGE / 2) + (SQUER_EDGE * path_int_cordinat[i]) ;
        convert.y = BEG_POINT_Y + (SQUER_EDGE / 2) + (SQUER_EDGE * path_int_cordinat[i + 1]);
        path_points.push_back(convert);
    }
    return path_points;
}

std::vector<Enemy*> Player::make_enemys(std::vector<int> number_of_each_enemy){
    std::vector<Enemy*> enemys;
    for(int i = 0; i < number_of_each_enemy[0]; i++){
        Runner* runner = new Runner(path, RUNNER_SPEED);
        enemys.push_back(runner);
    }
    for(int i = 0; i < number_of_each_enemy[1]; i++){
        Runner_stubborn* runner_stubborn = new Runner_stubborn(path, RUNNER_STUBBORN_SPEED);
        enemys.push_back(runner_stubborn);
    }
    for(int i = 0; i < number_of_each_enemy[2]; i++){
        Super_trooper* super_trooper = new Super_trooper(path, SUPER_TROOPER_SPEED);
        enemys.push_back(super_trooper);
    }
    for(int i = 0; i < number_of_each_enemy[3]; i++){
        Scrambler* scrambler = new Scrambler(path, SCRAMBLER_SPEED);
        enemys.push_back(scrambler);
    }    
    return enemys;
}

void Player::inititialize_all_enemy(std::vector<std::string> line_of_file){
    for(int i = 1; i < line_of_file.size(); i++){
        std::vector<Enemy*> one_wave_of_enemy = make_enemys(return_number_of_each_line(line_of_file[i]));
        enemys.push_back(one_wave_of_enemy);
    }
    lineup_enemy = enemys[0];
}

void Player::upgrade_tower(Point mouse_position){
    for(int i = 0; i < towers.size(); i++){
        if(!towers[i]->is_this_point_out_of_your_area(mouse_position)){
            if(towers[i]->is_tower_can_upgrade(money)){
                towers[i]->upgrade_tower();
                money -= towers[i]->get_tower_upgrade_cast();
                return;
            }
        }
    }
}

void Player::set_new_tower(int tower_name, Screen* screen_controler){
    Point mouse_position = screen_controler->get_mouse_point();
    if(!can_build_tower(tower_name, screen_controler))
        return;
    switch (tower_name){
        case 1:{
            Gatling* gatling = new Gatling(mouse_position);
            towers.push_back(gatling);
            money -= GATLING_CAST;
            break;
        }
        case 2:{
            Missile* missile = new Missile(mouse_position);
            towers.push_back(missile);
            money -= MISSILE_CAST;
            break;
        }
        case 3:{
            Tesla* tesla = new Tesla(mouse_position);
            towers.push_back(tesla);
            money -= TESLA_CAST;
            break;
        }
        case 4:{
            Glue* glue = new Glue(mouse_position);
            towers.push_back(glue);
            money -= GLUE_CAST;
            break;
        }
        default:
            break;
    }
}

bool Player::check_is_on_the_path(Point place){
    for(int i = 1; i < path.size(); i++){
        if(place.x > path[i].x - SQUER_EDGE / 2 && place.x < path[i].x + SQUER_EDGE / 2 && place.y > path[i].y - SQUER_EDGE / 2 && place.y < path[i].y + SQUER_EDGE / 2)
            return false;
    }
    return true;
}

bool Player::check_is_duplicat(Point place){
    for(int i = 0; i < towers.size(); i++){
        if(!towers[i]->is_this_point_out_of_your_area(place))
            return false;
    }
    return true;
}

bool Player::check_place(Point place){
    if(BEG_POINT_X > place.x || BEG_POINT_Y > place.y || place.x > (BEG_POINT_X + 19 * SQUER_EDGE) || place.y > (BEG_POINT_Y + 11 * SQUER_EDGE))
        return false;
    return true;
}

bool Player::can_build_tower(int tower_name, Screen* screen_controler){
    Point place = screen_controler->get_mouse_point();
    if(!check_place(place)){
        screen_controler->record_error(WRONG_OUT_OF_FIELD);
        return false;
    }
    if(!check_is_on_the_path(place)){
        screen_controler->record_error(WRONG_IN_PATH);
        return false;
    }
    if(!check_is_duplicat(place)){
        screen_controler->record_error(WRONG_DUPLICAT_TOWER);
        return false;
    }   
    switch (tower_name){
    case 1:{
        if(money < GATLING_CAST){
            screen_controler->record_error(WRONG_TOWER_CAST);
            return false;
        }
        break;
    }
    case 2:{
        if(money < MISSILE_CAST){
            screen_controler->record_error(WRONG_TOWER_CAST);
            return false;
        }
        break;
    }
    case 3:{
        if(money < TESLA_CAST){
            screen_controler->record_error(WRONG_TOWER_CAST);
            return false;
        }
        break;
    }
    case 4:{
        if(money < GLUE_CAST){
            screen_controler->record_error(WRONG_TOWER_CAST);
            return false;
        }
        break;
    }
    default:
        break;
    }
    return true;
}

bool Player::time_controler(){
    if(round == 1){
        return true;
    }
    else{
        if(time_round >= DELAY_TIME_FOR_WAVE) 
            return true;
        time_round += DELAY_PER_SECOND;
        return false;
    }
}

bool Player::control_gap_time_between_enemys(){
    if(!current_wave.empty()){
        if(gap_time_between_enemys >= DELAY_TIME_FOR_EACH_ENEMY){
            gap_time_between_enemys = 0;
            return true;
        }
        gap_time_between_enemys += DELAY_PER_SECOND;
        return false;
    }
    return true;
}

void Player::add_random_enemy_in_wave(){
    if(!lineup_enemy.empty()){
        int random_enemy_index = rand() % lineup_enemy.size();
        lineup_enemy[random_enemy_index]->set_round(round);
        lineup_enemy[random_enemy_index]->increas_health_by_round();
        current_wave.push_back(lineup_enemy[random_enemy_index]);
        lineup_enemy.erase(lineup_enemy.begin() + random_enemy_index);
    }
}

void Player::delete_reached_enemys(){
    for(int i = 0; i < current_wave.size(); i++){
        if(current_wave[i]->is_reached_finish_line()){
            heart -= current_wave[i]->get_heart();
            if(heart < 0)
                heart = 0;
            current_wave.erase(current_wave.begin() + i);
        }
    }
}

void Player::delete_killed_enemys(){
    for(int i = 0; i < current_wave.size(); i++){
        if(current_wave[i]->is_killed()){
            money += current_wave[i]->spend_gold_to_player();
            current_wave.erase(current_wave.begin()+ i);
        }
    }
}

void Player::round_controler(){
    if(round < enemys.size() && current_wave.empty() && lineup_enemy.empty()){
        round++;
        time_round = 0;
        current_wave.clear();
        lineup_enemy = enemys[round - 1];
    }
    else if(round == enemys.size() && current_wave.empty() && lineup_enemy.empty())
        round++;
}

void Player::enemy_wave_controler(){
    if(time_controler()){
        if(control_gap_time_between_enemys())
            add_random_enemy_in_wave();
        delete_killed_enemys();
        delete_reached_enemys();
        round_controler();
    }   
}

void Player::draw(Window* window){
    std::string file_name(FILE_NAME), font(FONT);
    std::string output("Hearts: "), output2("Gold: "), output3("Round: ");
    output += std::to_string(heart);
    output2 += std::to_string(money);
    output3 += std::to_string(round);
    window->show_text(output, Point(50, 50), WHITE, file_name + "/" + font, HEAD_FONT_SIZE);
    window->show_text(output2, Point(250, 50), WHITE, file_name + "/" + font, HEAD_FONT_SIZE);
    window->show_text(output3, Point(630, 50), WHITE, file_name + "/" + font, HEAD_FONT_SIZE);
    draw_path(window);
    for(int i = 0; i < towers.size(); i++)
        towers[i]->draw_in_screen(window);
    for(int i = 0; i < current_wave.size(); i++)
        current_wave[i]->draw_in_screen(window);
    if(is_play_ended()){
        if(whats_is_play_result())
            window->show_text(WIN_PHRASE, Point(570, 400), WHITE, file_name + "/" + font, RESULT_FONT_SIZE);////////////////////
        else
            window->show_text(LOSS_PHRASE, Point(570, 400), WHITE, file_name + "/" + font, RESULT_FONT_SIZE);//////////////
    }
}

void Player::upadat(){
    enemy_wave_controler();
    for(int i = 0; i < current_wave.size(); i++)
            current_wave[i]->move();
    for(int i = 0; i < towers.size(); i++)
        towers[i]->guard(current_wave);
}

bool Player::is_play_ended(){
    if(heart <= 0 || (round == enemys.size() + 1))
        return true;
    return false;
}

bool Player::whats_is_play_result(){
    return heart > 0;
}

void Player::clean(){
    for(int i = 0; i < towers.size(); i++)
        delete towers[i];
    towers.clear();
    for(int i = 0; i < enemys.size(); i++){
        for(int j = 0; j < enemys[i].size(); j++)
            delete enemys[i][j];
        enemys[i].clear();
    }
}