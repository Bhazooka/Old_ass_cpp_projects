#include <iostream>
#include "libPark.h"

using namespace std;
using namespace ParkSpace;

int main(int argc, char** argv)
{
    //Seed time for psuedo random
    srand(time(nullptr));
    //Check if number of arguments corresponds with requirements
    if(argc!=5)
    {
        cerr << "Theres not enough arguments to run the program";
        exit(ERR_ARGC);
    }

    //Convert argument strings to int
    int intRows = ConvertToInt(argv[1]);
    int intCols = ConvertToInt(argv[2]);
    int intTrees = ConvertToInt(argv[3]);
    int intBlueGrass = ConvertToInt(argv[4]);

    int intI_Trees = 4;

    //Range check for rows and cols
    RangeCheck(intRows, MIN_SPACE, MAX_SPACE);
    RangeCheck(intRows, MIN_SPACE, MAX_SPACE);

    //Assert to make sure values in bound
    assert(intRows > 0);
    assert(intCols > 0);
    assert(intTrees > 0);
    assert(intBlueGrass > 0);

    //Initialise world
    recWorld stcWorld = InitWorld(intRows, intCols, intTrees, intI_Trees, intBlueGrass);

    char Choice = '\0';
    bool blnContinue = true;

    do
    {
        //Print the world
        Display(stcWorld);
        //Input Player Option: for movement
        cin >> Choice;
        Choice = tolower(Choice);

        //Player Movement
        switch(Choice)
        {
        case 'w':
        case 'e':
        case 'd':
        case 'c':
        case 'x':
        case 'z':
        case 'a':
        case 'q':
            MovePlayer(stcWorld, Choice);
            break;
        case '`':
            blnContinue = false;
            break;
        default:
            cerr << "Invalid Option, Try again" << endl;
            break;
        }

        //Test to end game
        CheckEnd(stcWorld);
        if(stcWorld.GameStatus!=RUNNING)
        {
            blnContinue = false;
        }
    }while(blnContinue);

    //Dealloc memory
    FreeSpace(stcWorld.arrWorld, intRows);

    return SUCCESS;
}
