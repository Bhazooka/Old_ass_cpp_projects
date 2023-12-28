#ifndef LIBLITTER_H_INCLUDED
#define LIBLITTER_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace LitterSpace
{
    //you always have to declare this part as a const
    const int NUM_LEVELS = 20;
    const int NUM_LITTER = 5;

    const int VAL_WATER = 0;
    const int VAL_PILOT = 1;
    const int VAL_LITTER = 2;

    const char CH_WATER = '-';
    const char CH_PILOT = 'p';
    const char CH_LITTER = '*';

    const int MOVE_UP = 1;
    const int MOVE_DOWN = 2;

    const int ERR_PLAYER_NOT_FOUND = -1;

    int GetRand(int,int);
    void outputScreen (int arrNums[]);
    void InitGame(int arrNums[]); //arrays are never returns, and they are passed by refference by default.
    void MoveUser(int arrNums[], int Movement);
    void Pause();
    bool TestWon(int arrNums[]);


}


#endif // LIBLITTER_H_INCLUDED
