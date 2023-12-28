#include "libLitter.h"

namespace LitterSpace
{
    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to continue" << endl;
        cin.get();
    }

    int GetRand(int intLower, int intUpper)
    {
        int intRange = intUpper - intLower + 1;
        return rand()%intRange + intLower;
    }

    void InitGame(int arrNums[])
    {
        //Add water to each level
        for(int i=0;i<LEVEL;i++)
        {
            arrNums[i] = VAL_WATER;
        }

        //Place the litter
        for(int i=0;i<NUM_LITTER;i++)
        {
            //Get a random level
            int intLevel = GetRand(0,LEVEL-1);
            arrNums[intLevel] = VAL_LITTER;
        }

        //Place the pilot
        int intLevel = GetRand(0,LEVEL-1);
        arrNums[intLevel] = VAL_PILOT;
    }

    void OutputGame(int arrNums[])
    {
        //Output the features
        for(int n=0;n<LEVEL;n++)
        {
            switch(arrNums[n])
            {
            case VAL_LITTER:
                cout << CH_LITTER << endl;
                break;
            case VAL_PILOT:
                cout << CH_PILOT << endl;
                break;
            case VAL_WATER:
                cout << CH_WATER << endl;
                break;
            default:
                cerr<<"This line of code should never execute.  Wrong items in the array" << endl;
            }
        }

        //Output the prompt
        cout << "w: Move Up" << endl;
        cout << "s: Move Down" << endl;
        cout << "q: Quit" << endl;
    }

    void HandleMove(int arrNums[], int intMove)
    {
        //Find the level of the pilot
        int intCurrentLevel = -1;
        intCurrentLevel = FindPilot(arrNums);
        int intDestLevel = intCurrentLevel;
        if(intCurrentLevel==-1)
        {
            cerr << "Could not find the value. Exiting the program now" << endl;
            exit(ERR_NOT_FOUND);
        }

        //Calculated the destination location
        switch(intMove)
        {
        case MOVE_UP:
            intDestLevel--;
            break;
        case MOVE_DOWN:
            intDestLevel++;
            break;
        default:
            cerr << "Should not enter this line of code. HandleMove" << endl;
        }

        if(intDestLevel>=0 && intDestLevel < LEVEL)
        {
            arrNums[intDestLevel] = VAL_PILOT;
            arrNums[intCurrentLevel] = VAL_WATER;
        }

    }

    int FindPilot(int arrNums[])
    {
        int intLevel = -1;
        for(int n=0;n<LEVEL;n++)
        {
            if(arrNums[n]==VAL_PILOT)
                return n;
        }
        return intLevel;
    }

    bool HandleEnd(int arrNums[])
    {
        bool blnWon = true;
        for(int n=0;n<LEVEL;n++)
        {
            if(arrNums[n]==VAL_LITTER)
                return false;
        }

        return blnWon;
    }
}
