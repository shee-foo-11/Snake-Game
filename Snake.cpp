#include "Snake.h"

Snake::Snake(COORD pos, int vel){
    this->pos=pos;
    this->vel=vel;
    len=1;
    direction='n';

    body.push_back(pos);
}

void Snake::change_dir(char dir){
    direction=dir;
}

vector<COORD> Snake::get_body(){
    return body;
}

void Snake::move_snake(){
    switch(direction){
        case 'u':{
            pos.Y-=vel;
            break;
        }
        case 'd':{
            pos.Y+=vel;
            break;
        }
        case 'l':{
            pos.X-=vel;
            break;
        }
        case 'r':{
            pos.X+=vel;
            break;
        }
    }

    if(pos.X>WIDTH-2)pos.X=0;
    if(pos.X<1)pos.X=WIDTH-2;

    body.push_back(pos);
    if(body.size()>len){
        body.erase(body.begin());
    }
}

COORD Snake::get_pos(){
    return pos;
}

bool Snake::eaten(COORD food_pos){
    if(food_pos.X==pos.X and food_pos.Y==pos.Y)return 1;
    return 0;
}

void Snake::grow(){
    len++;
}

bool Snake::collided(){
    if(pos.X<1 || pos.X>WIDTH-2 || pos.Y<1 || pos.Y>HEIGHT-2)return 1;
    for(int i=0;i<len-1;i++){
        if(pos.X==body[i].X and pos.Y==body[i].Y)return 1;
    }
    return 0; 
}