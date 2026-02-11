#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <pthread.h>
#include "main.h"

int main()
{
    std::srand(std::time(0));
    int score = 0;
    bool gameoflag = false;
    std::cout << "snakegame."<< std::endl;
    int im[40][25];
    int foodx = rand()%40, foody = rand()%25;
    int x = 20, y = 13;
    for (int i = 0; i<40; i++)
    {
        for (int j = 0; j<25; j++)
        {
            if (i == foodx && j == foody)
            {
                im[i][j] = 1;
            }
            else
            {
                im[i][j] = 0;
            }
        }
    }
    /*[x][y], 25 = y 40 = x*/
    int TailX[40], TailY[40], len = 1;
    GameRender(im, score, x, y, len, TailX, TailY, 40, 25);
    do{
        UserInput;
        NextFrame(x, y, Dir, len, TailX, TailY, score, im);
        GameRender(im, score, x, y, len, TailX, TailY, 40, 25);
        gameoflag = GameOver(x, y, len, TailX, TailY, 40, 25, im);
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }while(gameoflag == false);
    return 0;
}