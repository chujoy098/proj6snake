#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "main.h"
#include <mutex>

int main()
{
    struct termios oldSettings, newSettings;
    std::srand(std::time(0));
    int score = 0;
    bool gameoflag = false;
    unsigned char choice;
    std::cout << "snakegame.snakegame.snakegame.snakegame.snakegame."<< std::endl;
    std::cout << "Begin?\nY/N:";
    do {
        std::cin >> choice;
    }while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
    if (choice == 'Y' || choice == 'y'){
        int speed;
        std::cout << "Enter time between frames in milliseconds (300 recommended): ";
        do {
            std::cin >> speed;
        }while (speed<=0);
        int im[20][40];
        int foodx = rand()%40, foody = rand()%25;
        int x = 20, y = 10;
        for (int i = 0; i<40; i++)
        {
            for (int j = 0; j<20; j++)
            {
                if (i == foodx && j == foody)
                {
                    im[j][i] = 1;
                }
                else
                {
                    im[j][i] = 0;
                }
            }
        }
        /*[y][x], 25 = y 40 = x*/
        int TailX[40], TailY[40], len = 0;
        GameRender(im, score, x, y, len, TailX, TailY);
        std::thread inp(Userinput);
        do{
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
            NextFrame(x, y, Dir, len,
        TailX, TailY, score, im);
            GameRender(im, score, x, y, len, TailX, TailY);
            gameoflag = GameOver(x, y, len, TailX, TailY);
        }while(gameoflag == false);
        std::cout << "Game Over! Start anew if you wish to continue.\n";
    }
    else {
      std::cout << "Ok.\n";
    }
    return 0;
}