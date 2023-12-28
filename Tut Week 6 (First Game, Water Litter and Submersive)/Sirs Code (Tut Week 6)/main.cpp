#include "libLitter.h"
#include <iostream>

using namespace std;
using namespace LitterSpace;

int main()
{
    srand(time(0));
    int arrGame[LEVEL];             //Array to store the game features
    char chInput = '\0';            //Input from the user
    bool blnContinue = true;        //Flag to test whether to end the game
    bool blnWon = false;            //To test if we won the game

    //Initialise the game
    InitGame(arrGame);
    do
    {
        //Output the screen
        system("cls");
        OutputGame(arrGame);

        //Get the input from the user
        cin >> chInput;

        //Handle the movement
        switch(chInput)
        {
        case 'w':
        case 'W':
            HandleMove(arrGame,MOVE_UP);
            break;
        case 's':
        case 'S':
            HandleMove(arrGame,MOVE_DOWN);
            break;
        case 'q':
        case 'Q':
            blnContinue = false;
            break;
        default:
            cerr << "Incorrect option, please try again" << endl;
            Pause();
        }

        //Test if end of the game
        blnWon = HandleEnd(arrGame);
        if(blnWon)
            blnContinue = false;
    }while(blnContinue);

    if(blnWon)
    {
        cout << "*********************************************************" << endl;
        cout << "*    Congratulations you collected all the litter       *" << endl;
        cout << "*********************************************************" << endl;
    }
    else
    {
        cout << "*********************************************************" << endl;
        cout << "*              You decided to quit the game             *" << endl;
        cout << "*********************************************************" << endl;
    }

    return 0;
}
