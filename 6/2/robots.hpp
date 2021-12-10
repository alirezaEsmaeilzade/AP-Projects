#ifndef __ROBOTS_H__
#define __ROBOTS_H__
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
class Channel;
class Robot{
    public: 
        virtual void update() = 0;
};
class Echo_robot : public Robot{
    public:
        Echo_robot(Channel* init_src_channel_, Channel* init_dest_channel);
        virtual void update();
    private:
        Channel* src_channel;
        Channel* dest_channel;
};
class Fred_robot : public Robot{
    public:
        Fred_robot(Channel* new_channel);
        virtual void update();
    private:
        void speak(){std::cout << "Hello" << std::endl;}
        Channel* channel;
};
class Librarian_robot : public Robot{
    public:
        Librarian_robot(Channel* new_channel);
        virtual void update();
    private:
        void speak(){std::cout << "Quiet!" << std::endl;}
        std::vector <std::string> quiet_massage;
        Channel* channel;
};
class Logger_robot : public Robot{
    public:
        Logger_robot(std::string file_name, std::vector <Channel*> channels);
        virtual void update();
    private:
        std::string file_name;
        std::vector <Channel*> channels;
};
#endif