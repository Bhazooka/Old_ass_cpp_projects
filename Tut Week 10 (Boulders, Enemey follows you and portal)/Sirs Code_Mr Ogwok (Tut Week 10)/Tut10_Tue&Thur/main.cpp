#include "libChase.h"
#include <ctime>
#include <cctype>

using namespace ChaseSpace;

int main(int argc, char** argv)
{
    srand(time(0));
    //Check argument count
    if(argc != 4){
       cerr << "Wrong number of command line arguments" << endl;
       exit(ERR_COUNT);
    }

    int intRows = convStrToInt(argv[1]);
    int intCols = convStrToInt(argv[2]);
    int intRange = convStrToInt(argv[3]);

    bool blnContinue = true;
    char chInput = '\0';

    GameWorld theGame = createGame(intRows, intCols, intRange);

    do{
        system("cls");
        printGame(theGame);

        cout << "Enter character to move" << endl
            << "w) Up s) Down a) Left d) Right" << endl
            << "Q ) Quit" << endl;

        cin >> chInput;
        chInput = tolower(chInput);

        switch(chInput){
            case 'w':
                {
                    movePlayer(theGame, UP);
                    break;
                }
            case 's':
                {
                    movePlayer(theGame, DOWN);
                    break;
                }
            case 'd':
                {
                    movePlayer(theGame, RIGHT);
                    break;
                }
            case 'a':
                {
                    movePlayer(theGame, LEFT);
                    break;
                }
            case 'q':
                {
                    blnContinue = false;
                }
            default:
                {
                    cerr << "Enter Valid Character" << endl;

                }
        }

        //Move Enemy / Update Game
        moveEnemy(theGame);

        cin.ignore(1000, '\n');
        cin.get();

        if(theGame.myGameState == WIN || theGame.myGameState == LOSS){
            blnContinue = false;
        }

    }while(blnContinue);

    if(theGame.myGameState == WIN){
        cout << "You won" << endl;
    }else if(theGame.myGameState == LOSS){
        cout << "You lost" << endl;
    }else if(theGame.myGameState = PLAY){
        cout << "You QUIT" << endl;
    }

    freeMemory(theGame.arrGame, theGame.intRows);

    return SUCCESS;
}
