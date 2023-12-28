#ifndef LIBWEIGHTS_H
#define LIBWEIGHTS_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cctype>
#include <iomanip>
#include <cassert>

using namespace std;

namespace ScaleSpace
{
    enum tError
    {
        SUCCESS,
        ERR_ARGC,
        ERR_CONV,
        ERR_RANGE
    };

    enum tState
    {
        RUNNING,
        WON,
        LOST,
        QUIT
    };

    typedef int* tOneArray;
    typedef int** tTwoArray;

    const int EMPTY = 0;
    const int WEIGHT = 1000;

    const char CH_EMPTY = '.';
    const char CH_WEIGHT = 'X';
    const char CH_PLAYER = 'P';

    struct tWorld
    {
        tTwoArray arrGame;
        int intRows;
        int intCols;
        int intCarry;
        int intPRow;
        int intPCol;
        tState enState;
    };

    int ConverStr(string strNum);
    tWorld InitWorld(int intRows, int intCols, int intWeights, int intScales);
    void Pause();
    void PrintWorld(tWorld strucWorld);
    void MovePlayer(tWorld& strucWorld, char chInput);
    void DropWeight(tWorld& strucWorld);
    void TestEnd(tWorld& strucWorld);
    void Dealloc(tTwoArray& arrGame, int intRows);


}

#endif
