#include "libChase.h"
#include <iostream>

using namespace std;
using namespace ChaseSpace;

int main(int argc, char** argv)
{
    //Seed the random number generator
    srand(time(nullptr));
    //Checks then number of command line arguments.
    if(argc!=4)
    {
        cerr << "Incorrect number of command line arguments" << endl;
        exit(ERR_ARGC);
    }

    //Safely converts string values to integers
    int intRows = GetInt(argv[1]);
    int intCols = GetInt(argv[2]);
    int intRange = GetInt(argv[3]);

    //Do a basic range check
    RangeCheck(intRows,5,30);
    RangeCheck(intCols,5,30);
    RangeCheck(intRange,1,30);

    //Intialise the game
    tGame stcGame = InitGame(intRows, intCols, intRange);
    bool blnContinue = true;
    char chInput = '\0';

    //Main loop
    do
    {
        //Print the world
        PrintWorld(stcGame);
        //Get input
        cin >> chInput;
        //Move the player
        chInput = tolower(chInput);
        switch(chInput)
        {
            case 'w':
                MovePlayer(stcGame, MOVE_UP);
                break;
            case 's':
                MovePlayer(stcGame, MOVE_DOWN);
                break;
            case 'a':
                MovePlayer(stcGame, MOVE_LEFT);
                break;
            case 'd':
                MovePlayer(stcGame, MOVE_RIGHT);
                break;
            case 'q':
                stcGame.enStatus = QUIT;
                break;
            default:
                cerr << "Incorrect option, please retry" << endl;
                Pause();
        }
        //Update - Move the enemy
        MoveEnemy(stcGame);
        //Update the main loop status
        if(stcGame.enStatus!=RUNNING)
            blnContinue = false;
    }while(blnContinue);

    cout << "********************************************************" << endl;
    if(stcGame.enStatus == QUIT)
        cout << "*                 YOU QUIT THE GAME                    *" << endl;
    if(stcGame.enStatus == WON)
        cout << "*                YOU ESCAPED THE GAME                  *" << endl;
    if(stcGame.enStatus == LOST)
        cout << "*      YOU WERE CAUGHT AND SENT BACK TO JAIL           *" << endl;
    cout << "********************************************************" << endl;
    Dealloc(stcGame.arrGame,stcGame.intRows);




    return 0;
}
