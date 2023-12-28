#include  "libWeights.h"

namespace ScaleSpace
{
    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to Continue" << endl;
        cin.get();
    }
    
    int GetRand(int intLower, int intHigher)
    {
        assert(intHigher >= intLower);
        int intRange=intHigher - intLower + 1;
        return rand()%intRange + intLower;
    }
    
    int ConverStr(string strNum)
    {
        stringstream ss {strNum};
        int intNum;
        ss >> intNum;
        if(ss.fail())
        {
            cerr  << "Could not convert string to int" << endl;
            exit(ERR_CONV);
        }
        return intNum;
    }
    
    tTwoArray AllocMem(int intRows, int intCols)
    {
        tTwoArray arrGame = new tOneArray[intRows];
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
    
    void PlaceFeature(tWorld& strucWorld, int intCount,int intFeature)
    {
        for(int n=0;n<intCount;n++)
        {
            int intRow = GetRand(0,strucWorld.intRows-1);
            int intCol = GetRand(0,strucWorld.intCols-1);
            while(strucWorld.arrGame[intRow][intCol]!=EMPTY)
            {
                intRow = GetRand(0,strucWorld.intRows-1);
                intCol = GetRand(0,strucWorld.intCols-1);
            }
            strucWorld.arrGame[intRow][intCol] = intFeature;
        }
    }
    
    tWorld InitWorld(int intRows, int intCols, int intWeights, int intScales)
    {
        tWorld strucWorld;
        strucWorld.intRows = intRows;
        strucWorld.intCols = intCols;
        strucWorld.arrGame = AllocMem(intRows, intCols);
        strucWorld.intPRow = intRows/2;
        strucWorld.intPCol = intCols/2;
        strucWorld.enState = RUNNING;
        strucWorld.intCarry = 0;
        PlaceFeature(strucWorld, intWeights,WEIGHT);
        
        for(int n=intScales-1;n>=1;n--)
        {
            int intTRange = intWeights - n;
            int intScaleValue = GetRand(1,intTRange);
            PlaceFeature(strucWorld, 1,intScaleValue);
            //cout << "Scale Value:" << intScaleValue << endl;
            intWeights -= intScaleValue;
        }
        PlaceFeature(strucWorld, 1,intWeights);
        //cout << "Scale Value:" << intWeights << endl;
        //Pause();
        
        return strucWorld;
    }
    
    
    void PrintWorld(tWorld strucWorld)
    {
        system("clear");
        for(int r=0;r<strucWorld.intRows;r++)
        {
            for(int c=0;c<strucWorld.intCols;c++)
            {
                cout << setw(2);
                int intFeature = strucWorld.arrGame[r][c];
                if(r==strucWorld.intPRow && c==strucWorld.intPCol)
                    cout << CH_PLAYER;
                else if(intFeature == EMPTY)
                    cout << CH_EMPTY;
                else if(intFeature == WEIGHT)
                    cout << CH_WEIGHT;
                else
                    cout << intFeature;
            }
            cout << endl;
        }
        cout << "w: Move Up" << endl
             << "e: Move Up+Right" << endl
             << "d: Move Right" << endl
             << "c: Move Down+Right" << endl
             << "x: Move Down" << endl
             << "z: Move Down+Left" << endl
             << "a: Move Left" << endl
             << "q: Move Up+Left" << endl
             << "p: Drop a weight" << endl
             << "m: Quit" << endl
             << "Carrying weight:" << strucWorld.intCarry << endl;
    }
    
    bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        return(intRow>=0 && intRow < intRows &&
               intCol>=0 && intCol < intCols);
    }
    
    void MovePlayer(tWorld& strucWorld, char chInput)
    {
        int intDRow = strucWorld.intPRow;
        int intDCol = strucWorld.intPCol;
        switch(chInput)
        {
            case 'w':
                intDRow--;
                break;
            case 'e':
                intDRow--;
                intDCol++;
                break;
            case 'd':
                intDCol++;
                break;
            case 'c':
                intDCol++;
                intDRow++;
                break;
            case 'x':
                intDRow++;
                break;
            case 'z':
                intDRow++;
                intDCol--;
                break;
            case 'a':
                intDCol--;
                break;
            case 'q':
                intDCol--;
                intDRow--;
                break;
        }
        
        if(IsInWorld(strucWorld.intRows, strucWorld.intCols, intDRow, intDCol))
        {
            //If the destination contains weight
            int intDFeature = strucWorld.arrGame[intDRow][intDCol];
            if(intDFeature == WEIGHT)
            {
                strucWorld.arrGame[intDRow][intDCol] = EMPTY;
                strucWorld.intCarry++;
            }
            //If the destination contains a scale
            else if(intDFeature > 0 && intDFeature < WEIGHT)
            {
                if(strucWorld.intCarry > 0)
                {
                    if(strucWorld.intCarry!=intDFeature)
                    {
                        strucWorld.enState = LOST;
                    }
                    else
                    {
                        strucWorld.arrGame[intDRow][intDCol] = EMPTY;
                        strucWorld.intCarry = 0;
                    }
                }
            }
            
            strucWorld.intPRow = intDRow;
            strucWorld.intPCol = intDCol;
        }
        
        
        
    }
    
    void DropWeight(tWorld& strucWorld)
    {
        if(strucWorld.intCarry<=0)
            return;
        int intLoc = GetRand(1,8);
        
        for(int n=0;n<8;n++)
        {
            int intDRow = strucWorld.intPRow;
            int intDCol = strucWorld.intPCol;
            int intSLoc = (intLoc + n)%8;
            cout << "intSloc:" << intSLoc << endl;
            Pause();
            switch(intSLoc)
            {
            case 1:
                intDRow--;
                break;
            case 2:
                intDRow--;
                intDCol++;
                break;
            case 3:
                intDCol++;
                break;
            case 4:
                intDCol++;
                intDRow++;
                break;
            case 5:
                intDRow++;
                break;
            case 6:
                intDRow++;
                intDCol--;
                break;
            case 7:
                intDCol--;
                break;
            case 0:
                intDCol--;
                intDRow--;
                break;
            }
            if(IsInWorld(strucWorld.intRows, strucWorld.intCols, intDRow, intDCol))
            {
                if(strucWorld.arrGame[intDRow][intDCol]==EMPTY)
                {
                    strucWorld.arrGame[intDRow][intDCol] = WEIGHT;
                    strucWorld.intCarry--;
                    return;
                }
            }
            
        }
        
        strucWorld.enState = LOST;
    }
    
    void TestEnd(tWorld& strucWorld)
    {
        for(int r=0;r<strucWorld.intRows;r++)
        {
            for(int c=0;c<strucWorld.intCols;c++)
            {
                int intFeature = strucWorld.arrGame[r][c];
                if(intFeature>0 && intFeature < WEIGHT)
                    return;
            }
        }
        strucWorld.enState = WON;
    }
    
    void Dealloc(tTwoArray& arrGame, int intRows)
    {
        assert(arrGame!=nullptr);
        for(int r=0;r<intRows;r++)
            delete[] arrGame[r];
        delete[] arrGame;
        arrGame = nullptr;
    }
    
}