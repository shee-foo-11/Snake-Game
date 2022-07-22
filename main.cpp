#include<iostream>


/*
library to pass shell/console commands: c standard library
We use the function "system" to send commands to the console.
*/
#include<cstdlib>


/*
library which includes functions to set the cursors position and over write the console.
*/
// #include<windows.h>

// library to capture the key strokes: console input output library
#include<conio.h>

/*
If we dont seed the random function, the food gets displayed in the same places always.
So to seed the random function we include this file.
*/
#include<ctime>


//(including Snakes.h takes care of the fact that windows.h has been included)
#include "Snake.h"
#include "Snake.cpp"

#include "Food.h"
#include "Food.cpp"

#include "Global.h"

/* 
Concept of "MACROS": 
They are one liner codes.
Instead of defining a function we can define a symbol

int sq(int x){
    return x*x;
}

instead=>

#define sq(x) x*x

similary;
#define WIDTH 50
#define HEIGHT 25

*/


using namespace std;

// defining a snake at the center of the screen : initial position
Snake snake({WIDTH/2,HEIGHT/2},1);

// creating a food object
Food food;

int score;

/*
struct COORD{
    int X;
    int Y;
};
if not on windows, define the COORD structure
*/

/*
In the coordiante system out computer uses, the y axis is flipped and the x axis is the same.
*/
// int x=10,y=10;

// const int WIDTH=50, HEIGHT=25;  =>defined as macros

void board(){
    COORD snake_pos=snake.get_pos();
    COORD food_pos=food.get_pos();

    vector<COORD> snake_body=snake.get_body();
    cout<<"SCORE : "<<score<<"\n\n";

    for(int i=0;i<HEIGHT;i++){
        cout<<"\t\t";
        cout<<"#";
        for(int j=0;j<WIDTH-2;j++){
            if(i==0 || i==HEIGHT-1)cout<<"#";
            else if(i==snake_pos.Y and j+1==snake_pos.X) cout<<"0";
            else if(i==food_pos.Y and j+1==food_pos.X) cout<<"X";
            else {
                bool is_body_part=0;
                for(int k=0;k<snake_body.size()-1;k++){
                    if(i==snake_body[k].Y and j+1==snake_body[k].X){
                        cout<<"o";
                        is_body_part=1;
                        break;
                    }
                }
                if(!is_body_part)cout<<" ";
            }
        }
        cout<<"#\n";
    }
}

int main(){
    score=0;
    srand(time(NULL));
    food.gen_food();

    bool gameOver=false;

    while(!gameOver){
        board();

        //detects keyborad hit
        if(kbhit()){
            // gives which key is pressed
            switch(getch()){
                case 'w':{
                    snake.change_dir('u');
                    break;
                }
                case 's':{
                    snake.change_dir('d');
                    break;
                }
                case 'a':{
                    snake.change_dir('l');
                    break;
                }
                case 'd':{
                    snake.change_dir('r');
                    break;
                }
            }
        }

        if(snake.collided())gameOver=1;
        if(snake.eaten(food.get_pos())){
            food.gen_food();
            snake.grow();
            score+=10;
        }

        
        snake.move_snake();

        // x++;
        // system("cls");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 7});

        /*

        We see the board flickering. And this is something we cant control 
        (fps/refresh rate => the properties of the console: it is a property of the operating system)
        We cant control something that belongs to the OS from an external source.

        One way of stooping this flickering is that instead of clearing the screen 
        [two processes going on-> clearing the screen and drawing the board]
        we can just over-write the board using the escape secquence

        this will work only on WINDOWS ( find a different library that does that on LINUX)
        => pick up the cursor from the end of the screen and go to origin and place the cursor there
        and then the data gets over written, which looks like the console has been cleared.

        #include <windows.h> => allows us to control the cursor's position on the console
        and instead of system ("cls") => SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD);
        where COORD is a data structure defined in windows.h which gets the cursor back to the mentioned coordinate.

        */
    }
}