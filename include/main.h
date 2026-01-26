#ifndef SNAKEGAME_MAIN_H
#define SNAKEGAME_MAIN_H
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 2

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction Dir = STOP;
bool ateflag = false;
void NextFrame(int x, int y, Direction D, int len, 
    int *TailX, int *TailY, int sc, unsigned char** map)
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
    if (map[x][y] = 'O') 
    {
        sc += 1;
        len++;
        map[x][y] = ' ';
        ateflag = true;
    }
}
bool GameOver(int x, int y, int len, int *TailX,
    int *TailY, int w, int h, unsigned char** im)
{
    // collision with wall
    if ((y >= h) || (x >= w) || (y < 0) ||
    (x < 0))
    {
        return true;
    }
    // collision with tail
    for (int i = 0; i < len; i++) 
    {
        if (TailX[i] == x && TailY[i] == y)
        {
            return true;
        }
    }
    return false;
}
#endif //SNAKEGAME_MAIN_H