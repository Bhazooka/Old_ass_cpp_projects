#include "libCatch.h"

namespace CatchSpace
{
    
    int GetRandom(int intLower, int intUpper)
    {
        int intRange = intUpper - intLower + 1;
        return rand()%intRange + intLower;
    }
    
    int GetInt(string strNum)
    {
        //User a stringstream class to try and convert
        stringstream ss{strNum};
        int intNum = 0;
        ss >> intNum;
        //If the conversion failed, then ss wil raise its fail flag
        if(ss.fail())
        {
            cerr << "Could not convert parameter to integer" << endl;
            exit(ERR_CONVERT);
        }
        return intNum;
    }
    
    void Dealloc(t_TwoArray& arrGame, int intRows)
    {
        for(int r=0;r<intRows;r++)
            delete[] arrGame[r];
        delete[] arrGame;
        arrGame = nullptr;
    }
    
    void PlaceFeature(t_TwoArray arrGame,int intRows, int intCols, int intFeature, int intCount)
    {
        //For each of the number of features
        for(int n=0;n<intCount;n++)
        {
            //Place the feature
            int intRow = GetRandom(0,intRows-1);
            int intCol = GetRandom(0,intCols-1);
            while(arrGame[intRow][intCol]!=EMPTY)
            {
                intRow = GetRandom(0,intRows-1);
                intCol = GetRandom(0,intCols-1);
            }
            arrGame[intRow][intCol] = intFeature;
        }
    }
    
    t_TwoArray InitGame(int intRows, int intCols)
    {
        t_TwoArray arrGame;
        //Allocate memory and initialise everything to empty
        arrGame = new t_OneArray[intRows];
        for(int r=0;r<intRows;r++)
        {
            arrGame[r]= new int[intCols];
            for(int c=0;c<intCols;c++)
            {
                arrGame[r][c] = EMPTY;
            }
        }
        
        PlaceFeature(arrGame,intRows, intCols,MAGIC,COUNT_MAGIC);
        PlaceFeature(arrGame,intRows, intCols,PLAYER,1);
        PlaceFeature(arrGame,intRows, intCols,ENEMY,1);
        return arrGame;
    }
    
    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to continue" << endl;
        cin.get();
    }
    
    void PrintWorld(t_TwoArray arrGame, int intRows, int intCols, int intMagic)
    {
        system("clear");
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                int intFeature = arrGame[r][c];
                cout << FEATURES[intFeature] << " ";
            }
            cout << endl;
        }
        cout << "w) Move Up" << endl
             << "s) Move Down" << endl
             << "a) Move Left" << endl
             << "d) Move Right" << endl
             << "q) Quit" << endl
             << "Collected Magic Items:" << intMagic << endl;
    }
    
    
    
    bool FindFeature(t_TwoArray arrGame, int intRows, int intCols, int& intRow, int& intCol, int intFeature)
    {
        intRow = -1;
        intCol = -1;
        
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                if(arrGame[r][c] == intFeature)
                {
                    intRow = r;
                    intCol = c;
                    return true;
                }
            }
        }
        return false;
    }
    
    bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        return (intRow>=0 && intRow<intRows &&
                intCol>=0 && intCol<intCols);
    }
    
    void MovePlayer(t_TwoArray arrGame, int intRows, int intCols, int& intMagic, char chInput)
    {
        //1 Get Current Location
        int intPRow = 0;
        int intPCol = 0;
        //If we did not find the feature
        if(!FindFeature(arrGame, intRows, intCols, intPRow, intPCol, PLAYER))
            return;
        //2 Calculate Destination Location
        int intDCol = intPCol;
        int intDRow = intPRow;
        switch(chInput)
        {
            case 'w':
                intDRow--;
                break;
            case 's':
                intDRow++;
                break;
            case 'a':
                intDCol--;
                break;
            case 'd':
                intDCol++;
                break;
        }
        
        //3 If In World
        if(IsInWorld(intRows, intCols, intDRow, intDCol))
        {
            //4 Update the World
            if(arrGame[intDRow][intDCol] == MAGIC)
            {
                intMagic++;
                arrGame[intDRow][intDCol] = PLAYER;
            }
            else
            {
                arrGame[intDRow][intDCol] = arrGame[intDRow][intDCol] + PLAYER;
            }
            arrGame[intPRow][intPCol] = arrGame[intPRow][intPCol] - PLAYER;
        }
    }
    
    void MoveRandomEnemy(t_TwoArray arrGame, int intRows, int intCols, int intRow, int intCol)
    {
        int intDRow = intRow;
        int intDCol = intCol;
        
        int intDLoc = GetRandom(1,8);
        if(intDLoc == 1)
        {
            intDRow--;
            intDCol--;
        }
        if(intDLoc == 2)
        {
            intDRow--;
        }
        if(intDLoc == 3)
        {
            intDRow--;
            intDCol++;
        }
        if(intDLoc == 4)
        {
            intDCol++;
        }
        if(intDLoc == 5)
        {
            intDRow++;
            intDCol++;
        }
        if(intDLoc == 6)
        {
            intDRow++;
        }
        if(intDLoc == 7)
        {
            intDRow++;
            intDCol--;
        }
        if(intDLoc == 8)
        {
            intDCol--;
        }
        if(IsInWorld(intRows, intCols, intDRow, intDCol))
        {
            arrGame[intDRow][intDCol] = arrGame[intDRow][intDCol] + ENEMY;
            arrGame[intRow][intCol] = arrGame[intRow][intCol] - ENEMY;
        }
    }
    
    bool IsInRange(int intX, int intY)
    {
        int intR = sqrt(pow(intX,2)+pow(intY,2));
        return(intR<RANGE);
    }
    
    void MoveEnemyTowards(t_TwoArray arrGame, int intRows, int intCols, int intRow, int intCol, int intPRow, int intPCol)
    {
        int intDRow = intRow;
        int intDCol = intCol;
        if(intPCol<intCol)
            intDCol--;
        if(intPCol>intCol)
            intDCol++;
        if(intPRow<intRow)
            intDRow--;
        if(intPRow>intRow)
            intDRow++;
        if(IsInWorld(intRows, intCols, intDRow, intDCol))
        {
            arrGame[intDRow][intDCol] = arrGame[intDRow][intDCol] + ENEMY;
            arrGame[intRow][intCol] = arrGame[intRow][intCol] - ENEMY;
        }
    }
    
    int GameEnd(t_TwoArray arrGame, int intRows, int intCols, int intMagic)
    {
        int intReturn = RUNNING;
        
        int intRow = 0;
        int intCol = 0;
        if(FindFeature(arrGame, intRows, intCols, intRow, intCol, ENEMY_PLAYER))
            return LOST;
        
        if(intMagic==COUNT_MAGIC)
            return WON;
        
        return intReturn;
    }
    
    void MoveEnemy(t_TwoArray arrGame, int intRows, int intCols)
    {
        //1 Get Current Location
        int intRow = 0;
        int intCol = 0;
        if(!FindFeature(arrGame, intRows, intCols, intRow, intCol, ENEMY))
        {
            if(!FindFeature(arrGame, intRows, intCols, intRow, intCol, ENEMY_MAGIC))
                return;
        }
        
        //2 Calculate Destination Location
        //3 If In World
        //4 Update the World
        int intPRow = 0;
        int intPCol = 0;
        if(!FindFeature(arrGame, intRows, intCols, intPRow, intPCol, PLAYER))
        {
            return;
        }
        int intX = abs(intPCol - intCol);
        int intY = abs(intPRow - intRow);
        if(IsInRange(intX, intY))
            MoveEnemyTowards(arrGame, intRows, intCols, intRow, intCol, intPRow, intPCol);
        else
            MoveRandomEnemy(arrGame, intRows, intCols, intRow, intCol);
        

    }
    
}