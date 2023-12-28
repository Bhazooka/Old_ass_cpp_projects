#include "libCatch.h"
#include <iostream>

using namespace std;
using namespace CatchSpace;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    if(argc!=3)
    {
        cerr << "Incorrect command line arguments" <<endl;
        cerr << "Please run " << argv[0] << " <TotalRows> <TotalCols>" << endl;
        exit(ERR_ARGC);
    }
    
    //Get initial variables
    int intRows = GetInt(argv[1]);
    int intCols = GetInt(argv[2]);
    int intStatus = RUNNING;
    
    //Basic Range Check
    if(intRows>MAX_SIZE || 
       intCols>MAX_SIZE || 
       intRows < MIN_SIZE || 
       intCols < MIN_SIZE)
    {
        cerr << "Command line arguments must be greater than " <<  MIN_SIZE << " and less than " << MAX_SIZE << endl;
        exit(ERR_RANGE);
    }
    
    //Initialise other variables
    int intMagic = 0;
    bool blnContinue = true;
    char chInput = '\0';
    t_TwoArray arrGame = InitGame(intRows, intCols);
    do
    {
        //Print World
        PrintWorld(arrGame, intRows, intCols, intMagic);
        //Get input
        cin >> chInput;
        //Handle input
        chInput = tolower(chInput);
        switch(chInput)
        {
            case 'w':
            case 's':
            case 'a':
            case 'd':
                //Handle the movement of the player
                MovePlayer(arrGame, intRows, intCols, intMagic, chInput);
                break;
            case 'q':
                blnContinue = false;
                break;
            default:
                cerr << "Incorrect option" << endl;
                Pause();
        }
        //Update
        MoveEnemy(arrGame, intRows, intCols);
        //Test for end game
        intStatus = GameEnd(arrGame,  intRows, intCols, intMagic);
        if(intStatus!=RUNNING)
            blnContinue = false;
    }while(blnContinue);
    
    PrintWorld(arrGame, intRows, intCols, intMagic);
    
    cout << "*************************************************************" << endl;
    switch(intStatus)
    {
        case WON:
            cout << "*      Congratulations you collected all the treasure       *" << endl;
            break;
        case LOST:
            cout << "*    Unfortunately you could not collect all the treasue    *" << endl;
            break;
            
    }
    cout << "*************************************************************" << endl;
    
    Dealloc(arrGame,intRows);
    
    
    
    
    
    
    
    return 0;
}