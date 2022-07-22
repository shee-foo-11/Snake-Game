#ifndef SNAKE_H
#define SNAKE_H
#include <windows.h>
#include<vector>
#include "Global.h"

using namespace std;

/*
position: position of the head;
length: length of the snake;
direction: the direction in which the snake is going;
velocity: how fast the snake is going(number of characters);
*/

class Snake{
    private:
        COORD pos;
        int len;
        int vel;
        char direction;
        vector<COORD> body;
    public:
        Snake(COORD pos,int vel);
        void change_dir(char dir);
        void move_snake();
        COORD get_pos();
        vector<COORD> get_body();

        bool eaten(COORD food_pos);
        void grow();
        bool collided();
};


#endif