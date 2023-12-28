#ifndef LIBLITTER_H
#define LIBLITTER_H

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace LitterSpace
{
    const int LEVEL = 20;
    const int NUM_LITTER = 5;

    const int VAL_WATER = 0;
    const int VAL_PILOT = 1;
    const int VAL_LITTER = 2;

    const char CH_WATER = '.';
    const char CH_PILOT = 'O';
    const char CH_LITTER = '*';

    const int ERR_NOT_FOUND = -1;

    const int MOVE_UP = 1;
    const int MOVE_DOWN = 2;

    void Pause();
    int GetRand(int intLower, int intUpper);
    void InitGame(int arrNums[]);
    void OutputGame(int arrNums[]);
    void HandleMove(int arrNums[], int intMove);
    int FindPilot(int arrNums[]);
    bool HandleEnd(int arrNums[]);

}

#endif // LIBLITTER_H
