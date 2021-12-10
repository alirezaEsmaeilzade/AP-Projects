#include "robots.hpp"
#include "channel.hpp"
Echo_robot::Echo_robot(Channel* init_src_channel_, Channel* init_dest_channel){
    this->src_channel = init_src_channel_;
    this->dest_channel = init_dest_channel;
    src_channel->attach(this);
    dest_channel->attach(this);
}
void Echo_robot::update(){
    if(src_channel->send_or_no()){
        std::string new_massage = src_channel->get_new_massage();
        src_channel->sended_to_echo_robot();
        dest_channel->set_massage(new_massage);
    }
}
Fred_robot::Fred_robot(Channel* new_channel){
    this->channel = new_channel;
    channel->attach(this);
}
void Fred_robot::update(){
    std::string new_massage = channel->get_new_massage();
    if(new_massage == "Hi"){
        speak();
    }
}
Librarian_robot::Librarian_robot(Channel* new_channel){
    this->channel = new_channel;
    channel->attach(this);
}
void Librarian_robot::update(){
    quiet_massage.push_back(channel->get_new_massage());
    if(quiet_massage.size() == 5){
        quiet_massage.clear();
        speak();
        quiet_massage.push_back("Quiet!");   
    }
}
Logger_robot::Logger_robot(std::string file_name, std::vector <Channel*> channels){
    this->file_name = file_name;
    this->channels = channels;
    for(int i = 0; i < channels.size(); i++)
        channels[i]->attach(this);
}
void Logger_robot::update(){
    std::ofstream output_file;
    output_file.open(file_name, std::fstream::app);
    for(int i = 0; i < channels.size(); i++){
        if(channels[i]->send_or_no()){
            output_file << channels[i]->get_new_massage() << std::endl;
            channels[i]->writed_in_file();
        }
    }
}