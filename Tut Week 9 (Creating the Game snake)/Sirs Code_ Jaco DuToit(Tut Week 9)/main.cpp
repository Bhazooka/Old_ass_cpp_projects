#include "libSnake.h"
#include <iostream>

using namespace SnakeSpace;
using namespace std;

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
    
    //Basic Range Check
    if(intRows>MAX_SIZE || 
       intCols>MAX_SIZE || 
       intRows < MIN_SIZE || 
       intCols < MIN_SIZE)
    {
        cerr << "Command line arguments must be greater than " <<  MIN_SIZE << " and less than " << MAX_SIZE << endl;
        exit(ERR_RANGE);
    }
    
    //Initialise the data structure
    tGame stcGame = InitGame(intRows, intCols);
    //Get initial variables
    bool blnContinue = true;
    char chInput = '\0';
    do
    {
        //PrintWorld
        PrintWorld(stcGame);
        //Get input
        cin >> chInput;
        
        //Move the snake
        chInput = tolower(chInput);
        switch(chInput)
        {
            case 'w':
                MoveSnake(stcGame, MOVE_UP);
                break;
            case 's':
                MoveSnake(stcGame, MOVE_DOWN);
                break;
            case 'a':
                MoveSnake(stcGame, MOVE_LEFT);
                break;
            case 'd':
                MoveSnake(stcGame, MOVE_RIGHT);
                break;
            case 'q':
                stcGame.enStatus = QUIT;
                break;
            default:
                cerr << "Incorrect option, please retry" << endl;
                Pause();
        }
        //Test for end
        if(stcGame.enStatus!=RUNNING)
            blnContinue = false;
    }while(blnContinue);
    
    PrintWorld(stcGame);
    
    switch(stcGame.enStatus)
    {
        case QUIT:
            cout << "See if you can beat your high score" << endl;
            break;
        case LOST:
            cout << "You lost!!" << endl;
            break;
    }
    
    Dealloc(stcGame.arrGame,stcGame.intRows);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return SUCCESS;
}