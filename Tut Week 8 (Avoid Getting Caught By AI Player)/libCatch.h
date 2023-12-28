#ifndef LIBCATCH_H_INCLUDED
#define LIBCATCH_H_INCLUDED

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cctype> //to use the tolower functions
#include <cmath>

using namespace std;

namespace CatchSpace
{
    //Const variables
    const int ERR_CONVERT = -1;
    const int ERR_ARGC = -2;
    const int ERR_RANGE = -3;

    const int MAX_SIZE = 20;
    const int MIN_SIZE = 5;
    const int COUNT_MAGIC = 10;

    const int EMPTY = 0;
    const int MAGIC = 1;
    const int PLAYER = 2;
    const int ENEMY = 3;
    const int ENEMY_MAGIC = 4;
    const int ENEMY_PLAYER = 5;

    const char FEATURES[6] = {'.','X','P','E','E','E'};

    const int RANGE = 5;

    typedef int* t_OneDArray;
    typedef int** t_TwoDArray;

    int GetInt(string strNum);
    t_TwoDArray InitGame(int intRows, int intCols);
    void PrintWorld(t_TwoDArray arrGame, int intRows, int intCols, int intMagic);
    void MovePlayer(t_TwoDArray arrGame, int intRows, int intCols, int &intMagic, char chInput); //Because we will be manipulating the 2d array it has to be passed by reference
    void MoveEnemy(t_TwoDArray arrGame, int intRows, int intCols);
    void Pause();

}

#endif // LIBCATCH_H_INCLUDED
