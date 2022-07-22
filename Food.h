#ifndef FOOD_H
#define FOOD_H
#include <windows.h>
#include "Global.h"
#include<cstdlib>

class Food{
    private:
        COORD pos;
    public:
        void gen_food();
        COORD get_pos();
};

#endif