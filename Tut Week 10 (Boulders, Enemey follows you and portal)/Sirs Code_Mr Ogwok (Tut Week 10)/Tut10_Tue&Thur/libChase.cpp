#include "libChase.h"
#include <sstream>
#include <cmath>

namespace ChaseSpace{

int convStrToInt(string strNum){
    int intNum = 0;
    stringstream ss {strNum};
    ss >> intNum;
    if(ss.fail()){
        cerr << "Failed to convert to integer" << endl;
        exit(ERR_CONV);
    }
    return intNum;
}

int generateRandNum(int intLower, int intUpper){
    int intRange = intUpper - intLower + 1;
    return rand() % intRange + intLower;
}

//Allocate Memory and Initialize Array Values
TwoDArray initArray(int intRows, int intCols){
    TwoDArray arrGame;
    arrGame = new OneDArray[intRows];
    for(int r = 0; r < intRows; r++){
        arrGame[r] = new int[intCols];
        for(int c = 0; c < intCols; c++){
            //Initialize Values to Space
            arrGame[r][c] = SPACE;
        }
    }
    return arrGame;
}

void placeFeature(GameWorld& myGameWorld, int intSRow, int intSCol, int intERow, int intECol, int intFeature){
    int intRow = generateRandNum(intSRow, intERow);
    int intCol = generateRandNum(intSCol, intECol);
    while(myGameWorld.arrGame[intRow][intCol] != SPACE){
        intRow = generateRandNum(intSRow, intERow);
        intCol = generateRandNum(intSCol, intECol);
    }
    //Place Feature
    myGameWorld.arrGame[intRow][intCol] = intFeature;
    //Check and Update Structure
    Coordinate featureCoordinate;
    if(intFeature == ENEMY){
        featureCoordinate = {intRow, intCol};
        myGameWorld.posEnemy = featureCoordinate;
    }else if(intFeature == PLAYER){
        featureCoordinate = {intRow, intCol};
        myGameWorld.posPlayer = featureCoordinate;
    }
}

GameWorld createGame(int intRows, int intCols, int intRange){
    GameWorld myGameWorld;
    myGameWorld.intRows = intRows;
    myGameWorld.intCols = intCols;
    myGameWorld.intEnemyRange = intRange;
    myGameWorld.myGameState = PLAY;
    //Array
    myGameWorld.arrGame = initArray(intRows, intCols);
    //Place Boulders
    for(int r = 0; r < intRows; r++){
        for(int c = 0; c < intCols; c++){
            int intChance = generateRandNum(0, 100);
            if(intChance <= BOULDER_CHANCE){
                myGameWorld.arrGame[r][c] = BOULDER;
            }
        }
    }

    //Place Enemy
    placeFeature(myGameWorld, 0, intCols/2, intRows/2, intCols - 1, ENEMY);
    //Place Escape Pod / Portal
    placeFeature(myGameWorld, 0, intCols/2, intRows/2, intCols - 1, PORTAL);
    //Place Player
    placeFeature(myGameWorld, intRows/2, 0, intRows - 1, intCols / 2, PLAYER);

    return myGameWorld;
}

void printGame(const GameWorld& myGameWorld){
    for(int r = 0; r < myGameWorld.intRows; r++){
        for(int c = 0; c < myGameWorld.intCols; c++){
            int index = myGameWorld.arrGame[r][c];
            cout << FEATURE_CHARS[index] << " ";
        }
        cout << endl;
    }
}

void freeMemory(TwoDArray& arrGame, int intRows){
    for(int r = 0; r < intRows; r++){
        delete [] arrGame[r];
    }
    delete [] arrGame;
    arrGame = nullptr;
}

bool isValidMove(int intRows, int intCols, int intDR, int intDC){
    return (intDR >= 0 && intDR < intRows && intDC>= 0 && intDC < intCols);
}

void movePlayer(GameWorld& myGameWorld, int chInput){
    int intDR = myGameWorld.posPlayer.intRow;
    int intDC = myGameWorld.posPlayer.intCol;

    switch(chInput){
        case UP:
            {
                intDR--;
                break;
            }
        case DOWN:
            {
                intDR++;
                break;
            }
        case LEFT:
            {
                intDC--;
                break;
            }
        case RIGHT:
            {
                intDC++;
                break;
            }
    }

    //Valid Destination?
    if(isValidMove(myGameWorld.intRows, myGameWorld.intCols, intDR, intDC) && myGameWorld.arrGame[intDR][intDC] != BOULDER){
        if(myGameWorld.arrGame[intDR][intDC] == ENEMY){
            myGameWorld.myGameState = LOSS;
            //Update Player Row and all the stuff
        }else if(myGameWorld.arrGame[intDR][intDC] == PORTAL){
            myGameWorld.myGameState = WIN;
            //Update Player Row and all the stuff
        }else{
            myGameWorld.arrGame[intDR][intDC] = PLAYER;
            myGameWorld.arrGame[myGameWorld.posPlayer.intRow][myGameWorld.posPlayer.intCol] = SPACE;
            //myGameWorld.posPlayer = {intDR, intDC};
            Coordinate playerPosition;
            playerPosition.intRow = intDR;
            playerPosition.intCol = intDC;
            myGameWorld.posPlayer = playerPosition;
        }
    }

}

bool isWithinRange(GameWorld myGameWorld){
    Coordinate playerPosition = myGameWorld.posPlayer;
    Coordinate enemyPosition = myGameWorld.posEnemy;

    int intX = abs(playerPosition.intCol - enemyPosition.intCol);
    int intY = abs(playerPosition.intRow - enemyPosition.intRow);
    int intRange = sqrt(pow(intX, 2) + pow(intY, 2));

    if(intRange <= myGameWorld.intEnemyRange){
        return true;
    }
    return false;
}

void moveEnemy(GameWorld& myGameWorld){
    int intDR = myGameWorld.posEnemy.intRow;
    int intDC = myGameWorld.posEnemy.intCol;

    //Enemy Position/ Coordinates
    int intER = myGameWorld.posEnemy.intRow;
    int intEC = myGameWorld.posEnemy.intCol;
    //Player Position/ Coordinates
    int intPR = myGameWorld.posPlayer.intRow;
    int intPC = myGameWorld.posPlayer.intCol;

    int intRandRow = 0;
    int intRandCol = 0;

    //Far from player?

    //Follow player
    if(isWithinRange(myGameWorld)){
        if(intPR < intER){
            intDR--;
        }
        if(intPR > intER){
            intDR++;
        }
        if(intPC < intEC){
            intDC--;
        }
        if(intPC > intEC){
            intDC++;
        }
    }else{ //Move Randomly
        intRandRow = generateRandNum(-1, 1);
        intRandCol = generateRandNum(-1, 1);
        intDR = intDR + intRandRow;
        intDC = intDC + intRandCol;
    }

    //Check valid destination
    if(isValidMove(myGameWorld.intRows, myGameWorld.intCols, intDR, intDC) && myGameWorld.arrGame[intDR][intDC] != BOULDER){
        if(myGameWorld.arrGame[intDR][intDC] == PLAYER){
            myGameWorld.myGameState = LOSS;
            //Update Player Row and all the stuff
        }else{
            myGameWorld.arrGame[intDR][intDC] = ENEMY;
            myGameWorld.arrGame[myGameWorld.posEnemy.intRow][myGameWorld.posEnemy.intCol] = SPACE;
            myGameWorld.posEnemy = {intDR, intDC};
        }
    }
}

}
