#ifndef SNAKEGAME_MAIN_H
#define SNAKEGAME_MAIN_H
#include <iostream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction Dir = STOP;
bool ateflag = false;
void NextFrame(int &x, int &y, Direction D, int &len,
    int *TailX, int *TailY, int &sc, int map[20][40])
{
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = y;
    TailY[0] = x; // this was in fact reversed indev; ignore the misleading names
    for (int i = 1; i < len; i++) 
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (Dir) {
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
        default:
            break;
    }
    // collision with food
    if (map[y][x] == 1)
    {
        sc += 1;
        len++;
        map[y][x] = 0;
        map[rand()%20][rand()%40] = 1;
        ateflag = true;
    }
}
bool GameOver(int x, int y, int len, int *TailX,
    int *TailY)
{
    // collision with wall
    if ((y > 20) || (x > 40) || (y < 0) ||
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
void GameRender(int im[20][40], int sc, int x,
    int y, int len, int *tailx, int *taily)
{
    system("clear");
    for (int i = 0; i < 40; i++)
    {
        std::cout << "-";
    }
    std::cout << "\n";
    for (int j = 0; j <= 20; j++) {
        for (int i = -1; i <= 40; i++)
        {
            if (i == -1)
            {
                std::cout << "|";
            }
            if (i == 40)
            {
                std::cout << "|\n";
            }
            if (i == x && j == y)
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
                    if (i<=39 && im[j][i] == 1)
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
    for (int i = 0; i < 40; i++)
    {
        std::cout << "-";
    }
    std::cout << "\n";
    std::cout << "Счёт: " << sc << std::endl;
}
void Userinput()
{
    struct termios oldSettings, newSettings;

    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );

    while ( 1 )
    {
        fd_set set;
        struct timeval tv;

        tv.tv_sec = 10;
        tv.tv_usec = 0;

        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );

        int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

        if( res > 0 )
        {
            char c;
            read( fileno( stdin ), &c, 1 );
            switch(c)
            {
                case 'w':
                    Dir = UP;
                    break;
                case 'a':
                    Dir = LEFT;
                    break;
                case 's':
                    Dir = DOWN;
                    break;
                case 'd':
                    Dir = RIGHT;
                    break;
                case 'W':
                    Dir = UP;
                    break;
                case 'A':
                    Dir = LEFT;
                    break;
                case 'S':
                    Dir = DOWN;
                    break;
                case 'D':
                    Dir = RIGHT;
                    break;
                default:
                    std::cout << "Possible user deviation";
                    break;
            }
        }
        else if( res < 0 )
        {
            perror( "select error" );
            break;
        }
        else
        {
            printf( "Select timeout\n" );
        }
    }
    tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
}
#endif //SNAKEGAME_MAIN_H

