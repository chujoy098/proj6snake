#ifndef SNAKEGAME_MAIN_H
#define SNAKEGAME_MAIN_H
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

struct termios oldt;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction Dir = STOP;
void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\nTerminal restored.\n");
}
void handle_sigint(int sig) {
    restore_terminal();
    exit(0);
}
bool ateflag = false;
void NextFrame(int x, int y, Direction D, int len, 
    int *TailX, int *TailY, int sc, int map[40][25])
{
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;
    for (int i = 1; i < len; i++) 
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (D) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    // collision with food
    if (map[x][y] == 1)
    {
        sc += 1;
        len++;
        map[x][y] = 0;
        ateflag = true;
    }
}
bool GameOver(int x, int y, int len, int *TailX,
    int *TailY, int w, int h, int im[40][25])
{
    // collision with wall
    if ((y >= h) || (x >= w) || (y < 0) ||
    (x < 0))
    {
        return true;
    }
    // collision with tail
    for (int i = 1; i < len; i++)
    {
        if (TailX[i] == x && TailY[i] == y)
        {
            return true;
        }
    }
    return false;
}
void GameRender(int im[40][25], int sc, int x,
    int y, int len, int *tailx, int *taily, int w, int h)
{
    system("clear");
    for (int i = 0; i < h + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int j = 0; j < h; j++) {
        for (int i = -1; i <= w+1; i++)
        {
            if (i == -1)
            {
                std::cout << "|";
            }
            if (i == w+1)
            {
                std::cout << "|\n";
            }
            if (i == y && j == x)
            {
                std::cout << "U";
            }
            else 
            {

                bool prTail = false;
                for (int k = 0; k < len; k++) {
                    if (tailx[k] == j
                        && taily[k] == i) 
                    {
                        std::cout << "#";
                        prTail = true;
                    }
                }
                if (!prTail)
                {
                    if (im[i][j] == 1)
                    {
                        std::cout<<"O";
                    }
                    else
                    {
                        std::cout<<" ";
                    }
                }

            }
        }
    }
    for (int i = 0; i < 30 + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    std::cout << "Счёт: " << sc << std::endl;
}
void UserInput()
{
    struct termios newt;
    char c;
    int useless;
    if (tcgetattr(STDIN_FILENO, &oldt) == -1) {
        perror("tcgetattr failed");
        return;
    }
    atexit(restore_terminal);
    signal(SIGINT, handle_sigint);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == -1) {
        perror("tcsetattr failed");
        return;
    }
    while (1) {
        if (read(STDIN_FILENO, &c, 1) == -1) {
            perror("read failed");
            return;
        }

        if (c == 'q') {
            break;
        }
    }
    switch(c)
    {
        case 'w':
            Dir = UP;
            std::cout << "i see you";
            break;
        case 'a':
               Dir = LEFT;
            std::cout << "i see you";
            break;
        case 's':
            Dir = DOWN;
            std::cout << "i see you";
            break;
        case 'd':
            Dir = RIGHT;
            std::cout << "i see you";
            break;
        case 'W':
            Dir = UP;
            std::cout << "i see you";
            break;
        case 'A':
            Dir = LEFT;
            std::cout << "i see you";
            break;
        case 'S':
            Dir = DOWN;
            std::cout << "i see you";
            break;
        case 'D':
            Dir = RIGHT;
            std::cout << "i see you";
            break;
        }
}
#endif //SNAKEGAME_MAIN_H

