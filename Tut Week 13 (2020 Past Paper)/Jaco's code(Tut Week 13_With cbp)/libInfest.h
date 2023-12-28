#ifndef LIBINFEST_H
#define LIBINFEST_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <sstream>
#include <cctype>

using namespace std;

namespace ParkSpace
{
    typedef int* tOneArray;
    typedef int** tTwoArray;

    //values for the lawn array
    enum tLawn
    {
        LAWN,
        BLUE
    };

    enum tErrors
    {
        SUCCESS,
        ERR_ARGC,
        ERR_CONV,
        ERR_RANGE
    };

    enum tState
    {
        RUNNING,
        LOST,
        WON,
        QUIT
    };

    enum tArray
    {
        TREE,
        GRASS
    };

    //const values for the tree array
    const int HEALTH_LOW = 11;
    const int HEALTH_HIGH = 20;
    const int SICK_LOW = 1;
    const int SICK_HIGH = 10;
    const int SICK_DEAD = 30;
    const int HEALTH_DEAD = 31;
    const int EMPTY = 0;
    const int PLAYER = 21;

    //output characters
    const char CH_PLAYER = 'P';
    const char CH_LAWN = '.';
    const char CH_BLUE = ',';
    const char CH_TREE_H = 'T';
    const char CH_TREE_S = 't';
    const char CH_TREE_H_B = 'F';
    const char CH_TREE_S_B = 'f';
    const char CH_TREE_DEAD = 'X';

    struct tWorld
    {
        tTwoArray arrTree;
        tTwoArray arrGrass;
        int intRows;
        int intCols;
        int intPRow;
        int intPCol;
        tState enState;
        string strEndMessage;
    };

    int StringToInt(string strNum);
    void RangeCheck(int intNum, int intLow, int intHigh);
    tWorld InitWorld(int intRows, int intCols, int intTrees, int intBlue);
    void PrintWorld(tWorld stcWorld);
    void Pause();
    void MovePlayer(tWorld& stcWorld, char chInput);
    void UpdateWorld(tWorld& stcWorld);
    void Dealloc(tTwoArray& arrVal, int intRows);
    void CheckEnd(tWorld& stcWorld);

}

#endif
