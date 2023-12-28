#include "libInfest.h"
#include <iostream>

using namespace std;
using namespace ParkSpace;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    if(argc != 5)
    {
        cerr << "Please provide the following arguments: <TotalRows> <TotalCols> <TotalTrees> <TotalBlueGrass>" << endl;
        exit(ERR_ARGC);
    }
    
    int intRows =StringToInt(argv[1]);
    int intCols =StringToInt(argv[2]);
    int intCountTrees =StringToInt(argv[3]);
    int intCountBlue =StringToInt(argv[4]);
    
    //Basic range checking
    RangeCheck(intRows,3,20);
    RangeCheck(intCols,2,20);
    RangeCheck(intCountTrees,1,(intRows*intCols)-1);
    RangeCheck(intCountBlue, 1, (intRows*intCols));
    
    //Get the basic variables
    tWorld stcWorld = InitWorld(intRows, intCols, intCountTrees, intCountBlue);
    bool blnContinue = true;
    char chInput = '\0';
    
    do
    {
        //Print the world
        PrintWorld(stcWorld);
        //Handle player movement
        cin >> chInput;
        chInput = tolower(chInput);
        switch(chInput)
        {
            case 'w':
            case 'e':
            case 'd':
            case 'c':
            case 'x':
            case 'z':
            case 'a':
            case 'q':
                MovePlayer(stcWorld, chInput);
                break;
            case 'm':
                stcWorld.enState = QUIT;
                stcWorld.strEndMessage = "You quit the game";
                break;
            default:
                cerr << "Incorrect option. Please select a valid option" << endl;
                Pause();
        }
        //Update
        UpdateWorld(stcWorld);
        //Check end
        CheckEnd(stcWorld);
        if(stcWorld.enState != RUNNING)
            blnContinue = false;
    }while(blnContinue);
    
    cout << stcWorld.strEndMessage << endl;
    
    Dealloc(stcWorld.arrTree,stcWorld.intRows);
    Dealloc(stcWorld.arrGrass,stcWorld.intRows);
    
    return 0;
}