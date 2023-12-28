#ifndef LIBCHASE_H_INCLUDED
#define LIBCHASE_H_INCLUDED

#include <iostream>

using namespace std;

namespace ChaseSpace{

const int BOULDER_CHANCE = 10;

enum StatusCodes{
    SUCCESS, ERR_COUNT, ERR_CONV
};

enum GameState{
    WIN, LOSS, PLAY
};

enum GameFeatures{
    SPACE, BOULDER, PLAYER, ENEMY, PORTAL
};

const char FEATURE_CHARS[5] = {'.', '0', 'P', 'E', 'X'};

typedef int* OneDArray;
typedef OneDArray* TwoDArray;

struct Coordinate {
    int intRow;
    int intCol;
};

struct GameWorld{
    int intRows;
    int intCols;
    TwoDArray arrGame;
    Coordinate posPlayer; // Player
    Coordinate posEnemy; // Enemy
    GameState myGameState;
    int intEnemyRange;
};

enum DIRECTION{
    UP, DOWN, LEFT, RIGHT
};


int convStrToInt(string strNum);

GameWorld createGame(int intRows, int intCols, int intRange);
void printGame(const GameWorld& myGameWorld);
void freeMemory(TwoDArray& arrGame, int intRows);
void movePlayer(GameWorld& myGameWorld, int chInput);
void moveEnemy(GameWorld& myGameWorld);
}

#endif // LIBCHASE_H_INCLUDED
