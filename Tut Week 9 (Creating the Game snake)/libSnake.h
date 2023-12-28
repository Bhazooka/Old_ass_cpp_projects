#ifndef LIBSNAKE_H
#define LIBSNAKE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cctype>

using namespace std;

namespace SnakeSpace
{
    //Const variables
    const int MAX_SIZE = 20;
    const int MIN_SIZE = 5;

    enum tErrors
    {
        SUCCESS,
        ERR_CONVERT = -1,
        ERR_ARGC = -2,
        ERR_RANGE = -3
    };

    enum tStatus
    {
        RUNNING,
        LOST,
        QUIT
    };

    enum tDirection
    {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT
    };

    const int HEAD = 1024;
    const int FRUIT = 2048;
    const int EMPTY = 0;
    const int BODY_START = 1;
    const int BODY_END = 1023;

    const char CH_HEAD = 'o';
    const char CH_BODY = '*';
    const char CH_FRUIT = '@';
    const char CH_EMPTY = '.';

    typedef int* t_OneArray;
    typedef int** t_TwoArray;

    struct tGame
    {
        t_TwoArray arrGame;
        int intRows;
        int intCols;
        int intPRow;
        int intPCol;
        int intScore;
        int intLength;
        tStatus enStatus;
    };

    int GetInt(string strNum);
    void Pause();
    tGame InitGame(int intRows, int intCols);
    void PrintWorld(tGame stcGame);
    void MoveSnake(tGame& stcGame, int intDirection);
    void Dealloc(t_TwoArray& arrGame, int intRows);


}


#endif
