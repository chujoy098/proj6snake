#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "include/main.h"
#include <random>

int main()
{
    std::srand(std::time(0));
    int score = 0;
    bool gameoflag = false;
    std::cout << "snakegame."<< std::endl;
    unsigned char** im = (unsigned char**)malloc(25 * sizeof(unsigned char*));
    int foodx = rand()%40, foody = rand()%25;
    int x = 20, y = 13;
    for (int i = 0; i<40; i++)
    {
        for (int j = 0; j<25; j++)
        {
            if (i == foodx && j == foody)
            {
                im[i][j] = 'O';
            }
            else
            {
                im[i][j] = ' ';
            }
        }
    }
    /*[x][y], 25 = y 40 = x*/
    int TailX[50], TailY[50], len = 1;
    do{
        
        NextFrame(x, y, Dir, len, TailX, TailY, score, im);

        gameoflag = GameOver(x, y, len, TailX, TailY, 40, 25, im);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }while(gameoflag = false);
    return 0;
}