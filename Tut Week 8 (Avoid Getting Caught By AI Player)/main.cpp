#include <iostream>
#include "libCatch.h"

using namespace std;
using namespace CatchSpace;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    if(argc!=3)
    {
        cerr << "Incorrect command line arguments" << endl;
        cerr << "Please run "<< argv[0] << "<TotalRows> <TotalCols>" << endl;
        exit(ERR_ARGC);
    }

    //Get variables from arguments
    int intRows = GetInt(argv[1]);
    int intCols = GetInt(argv[2]);

    //Basic range check
    if(intRows > MAX_SIZE || intCols > MAX_SIZE || intRows < MIN_SIZE || intCols < MIN_SIZE)
    {
        cerr << "Command line arguments must be greater than " << MIN_SIZE << " and less than " << MAX_SIZE << endl;
        exit(ERR_RANGE);
    }

    //Initialise other variables
    int intMagic = 0;
    bool blnContinue = true;
    char chInput = '\0';
    t_TwoDArray arrGame = InitGame(intRows, intCols);
    do
    {
        //Print the world
        PrintWorld(arrGame, intRows, intCols, intMagic);
        //Get input
        cin >> chInput;
        //handle input
        chInput = tolower(chInput); //I think it makes all character inputs to lower case
        switch(chInput)
        {
            case 'w':
            case 's':
            case 'a':
            case 'd':
                //Handl movement of the player
                MovePlayer(arrGame, intRows, intCols, intMagic, chInput);
                break;
            case 'q':
                blnContinue = false;
                break;
            default:
                cerr << "Incorrect option" << endl;
                Pause();
        }
        //update the world
        MoveEnemy(arrGame, intRows, intCols);
        //test for int game

    }while(blnContinue);









    return 0;
}
