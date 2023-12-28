//This is the implimentation file
#include "libLitter.h"

namespace LitterSpace
{
    int GetRand(int intLow,int intHigh)
    {
        int intRange = intHigh - intLow + 1;
        return rand() % intRange + intLow;
    }

    void outputScreen(int arrNums[])
    {
        for (int n=0; n < NUM_LEVELS; n++)
        {
            switch(arrNums[n])
            {

                case VAL_WATER:
                    cout << CH_WATER << endl;
                break;
                case VAL_PILOT:
                    cout << CH_PILOT << endl;
                break;
                case VAL_LITTER:
                    cout << CH_LITTER << endl;
                break;
                default:
                    cerr << "incorrect value for the array. Please troubleshoot.";
            }
        }

        cout << "w: Move up" << endl;
        cout << "s: Move up" << endl;
        cout << "a: Move up" << endl;
        cout << "d: Move up" << endl;
    }

    void InitGame(int arrNums[])
    {
        for (int n = 0; n< NUM_LEVELS; n++)
        {
            arrNums[n] = VAL_WATER;

        }

        //place five piece of litter
        for (int n = 0; n< NUM_LITTER; n++)
        {
            int intLevels = GetRand(0, NUM_LEVELS-1);
            arrNums[intLevels] = VAL_LITTER;
        }

        //Place the pilot in the array
        int intLevel = GetRand(0, NUM_LEVELS-1);
        arrNums[intLevel] = VAL_PILOT;

    }

    int FindPlayer(int arrNums[])
    {
        int intLocation = -1;
        for (int n = 0; n< NUM_LEVELS; n++)
        {
            if (arrNums[n] == VAL_PILOT)
                return n;

        }
        return intLocation;

    }

    void MoveUser(int arrNums[], int intMovement)
    {
        int intCurrentLoc = FindPlayer(arrNums);
        if (intCurrentLoc == -1)
        {
            cerr << "Couldnt find the player. Dangerous error";
            exit(ERR_PLAYER_NOT_FOUND);
        }

        int intDestLoc = intCurrentLoc;
        switch (intMovement)
        {
        case MOVE_DOWN:
            intDestLoc++;
            break;
            case MOVE_UP:
                intDestLoc--;
            break;
            default:
                cerr << "Not supposed to get into thi line of code. Move user" << endl;
        }
        if (intDestLoc>= 0 && intDestLoc< NUM_LEVELS)
        {
            arrNums[intDestLoc] = VAL_PILOT;
            arrNums[intCurrentLoc] = VAL_WATER;
        }
    }

    void Pause()
    {
        cin.ignore (100, '\n');

    }

    bool TestWon(int arrNums[])
    {
        bool blnWon = true;
        for (int n = 0; n< NUM_LEVELS; n++)
        {
            if (arrNums[n]==VAL_LITTER)
            {
                return false;
            }
        }
        return blnWon;
    }


}
