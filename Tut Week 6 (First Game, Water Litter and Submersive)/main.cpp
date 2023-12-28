#include "libLitter.h"
#include <iostream>

using namespace std;
using namespace LitterSpace;

int main()
{
    srand(time(0));

    //Basic variables that are required
    bool blnContinue = true;
    char chInput = '\0';
    int arrGame[NUM_LEVELS];
    bool blnWon = false;

    //initialise our game

    //Main loop
    do
    {

    //output game screen
    system("cls");
    outputScreen(arrGame);

    //get user input
    cin >> chInput;

    //handle input
    switch(chInput)
    {


    case 'W':
    case 'w':
        MoveUser(arrGame, MOVE_UP);
    case 'S':
    case 's':
        MoveUser(arrGame, MOVE_DOWN);
    case 'Q':
    case 'q':
        blnContinue = false;
    default:
        cerr << "Please select a valid option";
    }

    //determine if we won
    blnWon = TestWon(arrGame);


    }while(blnContinue);
    if (blnWon)
    {
        cout << "well done";

    }
    else
    {
        cout << "you suck";
    }

    return 0;
}
