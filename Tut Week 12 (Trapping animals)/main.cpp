#include <iostream>
#include "libHunt.h"

using namespace std;
using namespace HuntSpace;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    if(argc!=7)
    {
        cerr << "Please run " << argv[0] << " <TotalRows> <TotalCols> <TotalAnimals> <ChanceHuntingEquip> <PlayerRow> <PlayerCol>" << endl;
        exit(ERR_ARGC);
    }

    int intRows = ConvertStr(argv[1]);
    int intCols = ConvertStr(argv[2]);
    int intCountAnimal = ConvertStr(argv[3]);
    int intChanceHE = ConvertStr(argv[4]);
    int intPRow = ConvertStr(argv[5]);
    int intPCol = ConvertStr(argv[6]);

    //Do a basic check
    if(intPRow>=intRows || intPCol>=intCols)
    {
        cerr << "Please make sure to start the player in the boundary of the world" << endl;
        exit(ERR_RANGE);
    }

    //Get initial variables
    tGame strucGame = InitWorld(intRows, intCols, intCountAnimal, intChanceHE, intPRow, intPCol);
    bool blnContinue = true;
    char chInput = '\0';

    do
    {
        //Print the world
        PrintWorld(strucGame);
        //Move the player
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
            case 'p':
                MovePlayer(strucGame, chInput);
                break;
            case 'm':
                strucGame.enState = QUIT;
                break;
            default:
                cerr << "Incorrect option, please retry" << endl;
                Pause();
        }
        //Move the animals
        MoveAnimals(strucGame);

        //Update the game
        Update(strucGame);

        //Test end game
        EndGame(strucGame);

        if(strucGame.enState != RUNNING)
            blnContinue = false;
    }while(blnContinue);

    Dealloc(strucGame.arrGame,strucGame.intRows);

    return SUCCESS;
}
