#ifndef LIBHUNT_H
#define LIBHUNT_H

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <sstream>
#include <cctype>

using namespace std;

namespace HuntSpace
{
    typedef int* tOneDArray;
    typedef int** tTwoDArray;
    
    enum tReturn
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
        ANIMAL,
        H_EQUIPMENT,
        TRAP
    };
    
    const char FEATURES[5] = {'.','P','O','!','X'};
    
    enum tState
    {
        RUNNING,
        WIN,
        LOSE,
        QUIT
    };
    
    struct tGame
    {
        tTwoDArray arrGame;
        int intRows;
        int intCols;
        int intPRow;
        int intPCol;
        int intKnife;
        int intTrap;
        tState enState;
        int intCaught;
        int intKnifed;
        int intChanceHE;
    };
    
    int ConvertStr(string strNum);
    tGame InitWorld(int intRows, int intCols, int intCountAnimal, int intChanceHE, int intPRow, int intPCol);
    void PrintWorld(tGame strucGame);
    void MovePlayer(tGame& strucGame, char chInput);
    void Pause();
    void MoveAnimals(tGame& strucGame);
    void Dealloc(tTwoDArray& arrGame, int intRows);
    void Update(tGame& strucGame);
    void EndGame(tGame& strucGame);
}

#endif