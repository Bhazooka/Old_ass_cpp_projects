#ifndef LIBCATCH_H
#define LIBCATCH_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cctype>
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
    const int PLAYER =2;
    const int ENEMY = 3;
    const int ENEMY_MAGIC = 4;
    const int ENEMY_PLAYER = 5;
    
    const char FEATURES[6] = {'.','X','P','E','E','E'};

    const int RANGE = 5;
    
    typedef int* t_OneArray;
    typedef int** t_TwoArray;
    
    const int RUNNING = 1;
    const int LOST = 2;
    const int WON =3;
    
    int GetInt(string strNum);
    t_TwoArray InitGame(int intRows, int intCols);
    void PrintWorld(t_TwoArray arrGame, int intRows, int intCols, int intMagic);
    void MovePlayer(t_TwoArray arrGame, int intRows, int intCols, int& intMagic, char chInput);
    void MoveEnemy(t_TwoArray arrGame, int intRows, int intCols);
    void Dealloc(t_TwoArray& arrGame, int intRows);
    int GameEnd(t_TwoArray arrGame, int intRows, int intCols, int intMagic);
    void Pause();
}


#endif