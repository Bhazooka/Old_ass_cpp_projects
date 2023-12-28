#ifndef LIBCHASE_H
#define LIBCHASE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cassert>
#include <cctype>
#include <cmath>

using namespace std;

namespace ChaseSpace
{
    enum tReturns
    {
        SUCCESS,
        ERR_ARGC,
        ERR_CONV,
        ERR_RANGE
    };
    
    enum tFeatures
    {
        EMPTY,
        PLAYER,
        PORTAL,
        BOULDER,
        ENEMY,
        ENEMY_PLAYER
    };
    
    enum tStatus
    {
        RUNNING,
        QUIT,
        WON,
        LOST
    };
    
    enum tMove
    {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT
    };
    
    const char CH_FEATURES[6] = {'.','P','X','O','E','E'};
    
    typedef int* t1DArray;
    typedef int** t2DArray;
    
    struct tGame
    {
        int intRows;
        int intCols;
        tStatus enStatus;
        t2DArray arrGame;
        int intPRow;
        int intPCol;
        int intERow;
        int intECol;
        int intRange;
    };
    const int CHANCE_BOULDER = 10;
    
    
    int GetInt(string strNum);
    void RangeCheck(int intValue, int intLow, int intHigh);
    tGame InitGame(int intRows, int intCols, int intRange);
    void PrintWorld(tGame stcGame);
    void MovePlayer(tGame& stcGame, int intMovement);
    void Pause();
    void MoveEnemy(tGame& stcGame);
    void Dealloc(t2DArray& arrGame, int intRows);
    
    
}

#endif