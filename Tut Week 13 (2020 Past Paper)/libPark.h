#ifndef LIBPARK_H_INCLUDED
#define LIBPARK_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <cassert>

using namespace std;

namespace ParkSpace
{
    enum E_Errors
    {
        ERR_ARGC, ERR_SPACE, ERR_CONV, ERR_RANGE
    };

    enum E_Objects
    {
        LAWN, PLAYER, TREE, I_TREE, BLUEGRASS
    };

    //Characters to display in world
    const char OBJECTS[5] = {'.','P','#','I','*'};

    enum E_Status
    {
        SUCCESS, WIN, LOSE, QUIT, RUNNING
    };


    const int MIN_SPACE = 10;
    const int MAX_SPACE = 20;

    typedef int* oneDarr;
    typedef int** twoDarr;

    struct recWorld
    {
        twoDarr arrWorld;
        int intRows;
        int intCols;
        int PlayerRow;
        int PlayerCol;
        int intTrees;
        int intI_Trees;            //Infected trees
        int intBlueGrass;
        E_Status GameStatus;
    };


    int ConvertToInt(string strNum);
    void RangeCheck(int intValue, int intLow, int intHigh);
    twoDarr AllocMem(int intRows, int intCols);
    recWorld InitWorld(int intRows, int intCols, int intTrees, int intI_Trees, int intBlueGrass);
    void Display (recWorld stcWorld);
    void MovePlayer(recWorld& stcWorld, int Choice);
    void CheckEnd(recWorld& stcWorld);
    twoDarr FreeSpace(twoDarr& arrWorld, int intRows);

}



#endif // LIBPARK_H_INCLUDED
