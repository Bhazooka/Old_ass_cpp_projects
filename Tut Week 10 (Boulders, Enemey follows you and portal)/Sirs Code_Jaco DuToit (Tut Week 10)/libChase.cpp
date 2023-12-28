#include "libChase.h"

namespace ChaseSpace
{
    int GetRandom(int intLower, int intHigher)
    {
        assert(intHigher>intLower);
        int intRange = intHigher - intLower + 1;
        return rand()%intRange + intLower;
    }
    
    int GetInt(string strNum)
    {
        int intNum;
        stringstream ss {strNum};
        ss >> intNum;
        if(ss.fail())
        {
            cerr << "Could not convert string to integer" << endl;
            exit(ERR_CONV);
        }
        return intNum;
    }
    
    void RangeCheck(int intValue, int intLow, int intHigh)
    {
        if(intValue < intLow ||
           intValue > intHigh)
        {
            cerr << intValue << " is either less than " << intLow << " or greater than " << intHigh << endl;
            exit(ERR_RANGE);
        }
    }
    
    t2DArray AllocMem(int intRows, int intCols)
    {
        t2DArray arrGame;
        arrGame = new t1DArray[intRows];
        for(int r=0;r<intRows;r++)
        {
            arrGame[r] = new int[intCols];
            for(int c=0;c<intCols;c++)
            {
                arrGame[r][c] = EMPTY;
            }
        }
        
        return arrGame;
    }
    
    void PlaceFeature(tGame& stcGame, int intRowFrom, int intRowTo,
                      int intColFrom, int intColTo, int intFeature,
                      int& intRow, int& intCol)
    {
        intRow = GetRandom(intRowFrom, intRowTo);
        intCol = GetRandom(intColFrom, intColTo);
        while(stcGame.arrGame[intRow][intCol]!=EMPTY)
        {
            intRow = GetRandom(intRowFrom, intRowTo);
            intCol = GetRandom(intColFrom, intColTo);
        }
        stcGame.arrGame[intRow][intCol]=intFeature;
    }
    
    tGame InitGame(int intRows, int intCols, int intRange)
    {
        tGame stcGame;
        stcGame.arrGame = AllocMem(intRows, intCols);
        //Place the boulder
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                if(GetRandom(1,100) <= CHANCE_BOULDER)
                {
                    stcGame.arrGame[r][c] = BOULDER;
                }
            }
        }
        //Place the portal
        int intRow=0;
        int intCol=0;
        PlaceFeature(stcGame, 0, intRows/2,intCols/2, intCols-1, PORTAL, intRow, intCol);
        
        //Place the enemy
        PlaceFeature(stcGame, 0, intRows/2,intCols/2, intCols-1, ENEMY, intRow, intCol);
        stcGame.intERow = intRow;
        stcGame.intECol = intCol;
        
        //Place the player
        PlaceFeature(stcGame, intRows/2, intRows-1 ,0, intCols/2, PLAYER, intRow, intCol);
        stcGame.intPRow = intRow;
        stcGame.intPCol = intCol;
        
        //Set the rest of the struc values
        stcGame.intRows = intRows;
        stcGame.intCols = intCols;
        stcGame.enStatus = RUNNING;
        stcGame.intRange = intRange;
        
        return stcGame;
    }
    
    void PrintWorld(tGame stcGame)
    {
        system("clear");
        for(int r=0;r<stcGame.intRows;r++)
        {
            for(int c=0;c<stcGame.intCols;c++)
            {
                int intFeature = stcGame.arrGame[r][c];
                cout << CH_FEATURES[intFeature] << " ";
            }
            cout << endl;
        }
        cout << "w) Move up" << endl
             << "s) Move down" << endl
             << "a) Move left" << endl
             << "d) Move right" << endl
             << "q) Quit" << endl;
    }
    
    bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        return (intRow>=0 && intRow < intRows &&
                intCol>=0 && intCol < intCols);
    }
    
    void MovePlayer(tGame& stcGame, int intMovement)
    {
        assert(stcGame.arrGame!=nullptr);
        int intDRow = stcGame.intPRow;
        int intDCol = stcGame.intPCol;
        switch(intMovement)
        {
            case MOVE_UP:
                intDRow--;
                break;
            case MOVE_DOWN:
                intDRow++;
                break;
            case MOVE_LEFT:
                intDCol--;
                break;
            case MOVE_RIGHT:
                intDCol++;
                break;
        }
        if(IsInWorld(stcGame.intRows, stcGame.intCols, intDRow, intDCol))
        {
            //See if we moved into the enemy
            if(intDRow == stcGame.intERow && intDCol == stcGame.intECol)
            {
                stcGame.enStatus = LOST;
                return;
            }
            
            //See if we moved into the portal
            if(stcGame.arrGame[intDRow][intDCol]==PORTAL)
            {
                stcGame.enStatus = WON;
                return;
            }
            
            //Move if it is empty
            if(stcGame.arrGame[intDRow][intDCol]==EMPTY)
            {
                stcGame.arrGame[stcGame.intPRow][stcGame.intPCol] = EMPTY;
                stcGame.arrGame[intDRow][intDCol] = PLAYER;
                stcGame.intPRow = intDRow;
                stcGame.intPCol = intDCol;
            }
            
                
        }
    }
    
    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to continue" << endl;
        cin.get();
    }
    
    bool IsInRange(tGame& stcGame)
    {
        int y = stcGame.intPRow - stcGame.intERow;
        int x = stcGame.intPCol - stcGame.intECol;
        
        int r = sqrt((x*x)+(y*y));
        if(r<stcGame.intRange)
            return true;
        
        return false;
    }
    
    void MoveEnemy(tGame& stcGame)
    {
        assert(stcGame.arrGame!=nullptr);
        int intDRow = stcGame.intERow;
        int intDCol = stcGame.intECol;
        //Move the enemy towards the player if in range
        if(IsInRange(stcGame))
        {
            if(stcGame.intPRow > stcGame.intERow)
                intDRow++;
            if(stcGame.intPRow < stcGame.intERow)
                intDRow--;
            if(stcGame.intPCol < stcGame.intECol)
                intDCol--;
            if(stcGame.intPCol > stcGame.intECol)
                intDCol++;
        }
        else  //Do random movement
        {
            int intRowMovement = GetRandom(-1,1);
            int intColMovement = GetRandom(-1,1);
            intDRow = intDRow + intRowMovement;
            intDCol = intDCol + intColMovement;
        }
        
        if(IsInWorld(stcGame.intRows, stcGame.intCols, intDRow, intDCol))
        {
            //See if we caught the player
            if(intDRow == stcGame.intPRow && intDCol == stcGame.intPCol)
            {
                stcGame.enStatus = LOST;
                return;
            }
            
            //See if the destination is empty then move
            if(stcGame.arrGame[intDRow][intDCol]==EMPTY)
            {
                stcGame.arrGame[stcGame.intERow][stcGame.intECol] = EMPTY;
                stcGame.arrGame[intDRow][intDCol] = ENEMY;
                stcGame.intERow = intDRow;
                stcGame.intECol = intDCol;
            }
        }
    }
    
    void Dealloc(t2DArray& arrGame, int intRows)
    {
        assert(arrGame!=nullptr);
        for(int r=0;r<intRows;r++)
            delete[] arrGame[r];
        delete[] arrGame;
        arrGame = nullptr;
    }
    
    
    
    
    
    
    
    
    
    
}