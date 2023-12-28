#include "libWeights.h"  //THIS IS DU TOITS
#include <iostream>

using namespace ScaleSpace;
using namespace std;

int main(int argc, char** argv)
{
    srand(time(nullptr));

    if(argc!=5)
    {
        cerr << "Please run " << argv[0] << " TotalRows TotalCols TotalWeights TotalScales" << endl;
        exit(ERR_ARGC);
    }

    int intRows = ConverStr(argv[1]);
    int intCols = ConverStr(argv[2]);
    int intWeights = ConverStr(argv[3]);
    int intScales = ConverStr(argv[4]);

    if(intScales > intWeights)
    {
        cerr  << "The number of scales cannot be greater than the number of weights" << endl;
        exit(ERR_RANGE);
    }

    tWorld strucWorld = InitWorld(intRows, intCols, intWeights, intScales);
    bool blnContinue = true;
    char chInput = '\0';
    do
    {
        //Print World
        PrintWorld(strucWorld);
        //Get input
        cin >> chInput;
        //Move player
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
                //Move the player
                MovePlayer(strucWorld, chInput);
                break;
            case 'p':
                //Drop a weight
                DropWeight(strucWorld);
                break;
            case 'm':
                strucWorld.enState = QUIT;
                break;
            default:
                cerr << "Incorrect option, please try again" << endl;
                Pause();

        }
        //Test end
        TestEnd(strucWorld);
        if(strucWorld.enState!=RUNNING)
            blnContinue = false;
    }while(blnContinue);

    Dealloc(strucWorld.arrGame, strucWorld.intRows);

    return 0;
}
