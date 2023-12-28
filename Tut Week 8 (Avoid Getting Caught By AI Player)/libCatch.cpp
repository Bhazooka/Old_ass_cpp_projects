#include "libCatch.h"

namespace CatchSpace
{
    int GetRand(int intLower, int intUpper)
    {
        int intRange = intUpper - intLower + 1;
        return rand()%intRange + intLower;
    }

    int GetInt(string strNum)
    {
        //Use a stringstream class to try and convert
        stringstream ss(strNum);
        int intNum = 0;
        ss >> intNum;
        //If the conversion failed
        if (ss.fail())
        {
            cerr << "Couldnt convert parameter to integer" << endl;
            exit(ERR_CONVERT);
        }
        return intNum;
    }

    //This is a local variable, we dont have to place it in the header file
    void PlaceFeature(t_TwoDArray arrGame, int intRows, int intCols, int intFeature, int intCount)
    {
        //For each of the number of features
        for(int n=0; n<intCount ; n++)
        {
            //Place features
            int intRow = GetRand(0, intRows-1); //Generate random location in array
            int intCol = GetRand(0, intCols-1);
            while(arrGame[intRow][intCol]!=EMPTY) //If the block in our 2d array is not empty then you get another random. If theres already something inside (if the value is not EMPTY (We set empty to = 0), we generate another random block to place a feature)
            {
                intRow = GetRand(0, intRows-1);
                intCol = GetRand(0, intCols-1);
            }
            arrGame[intRow][intCol] = intFeature;
        }
    }

    t_TwoDArray InitGame(int intRows, int intCols)
    {
        t_TwoDArray arrGame;
        //Aloccate memory and initialise everything to 0
        arrGame = new t_OneDArray[intRows];
        for (int r=0; r < intRows; r++)
        {
            arrGame[r] = new int[intCols];
            for(int c=0; c<intCols; c++)
            {
                arrGame[r][c] = EMPTY;
            }
        }

        PlaceFeature(arrGame, intRows, intCols, MAGIC, COUNT_MAGIC);
        PlaceFeature(arrGame, intRows, intCols, PLAYER,1);
        PlaceFeature(arrGame, intRows, intCols, ENEMY,1);
        return arrGame;
    }

    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to continue" << endl;
        cin.get();
    }

    void PrintWorld(t_TwoDArray arrGame, int intRows, int intCols, int intMagic)
    {
        system("cls");
        for(int r=0; r < intRows; r++)
        {
            for(int c=0; c < intCols; c++)
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
             << "Collected Magical Items: "<< intMagic << endl;
    }

    bool FindFeature(t_TwoDArray arrGame, int intRows, int intCols, int& intRow, int& intCol, int intFeature) //The &intRow and &intCol is there to be updated. Its the position of the player that will be called by reference to change the value in the entire program when user chooses to move
    {
        intRow = -1;
        intCol = -1;

        for(int r=0; r < intRows; r++)
        {
            for(int c=0; c < intCols; c++)
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
        return (intRow>=0 && intRow < intRows &&
                intCol>=0 && intCol < intCols);
    }

    void MovePlayer(t_TwoDArray arrGame, int intRows, int intCols, int &intMagic, char chInput) //Because we will be manipulating the 2d array it has to be passed by reference
    {
        //1. Get Current location
        int intPRow = 0;
        int intPCol = 0;
        //if we did not find the feature
        if(!FindFeature(arrGame, intRows, intCols, intPRow, intPCol, PLAYER))
        {
            return;
        }
        //2. Calculate Destination
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
        //3. If in world
        if(IsInWorld(intRows, intCols, intDRow, intDCol))
        {
            //4. Update the world
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

    void MoveRandomEnemy(t_TwoDArray arrGame, int intRows, int intCols, int intRow, int intCol)
    {
        int intDRow = intRow;
        int intDCol = intCol;

        int intDLoc = GetRand(1,8);
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
        int intR = sqrt(pow(intX,2) + pow(intY,2));
        return(intR<RANGE);
    }

    void MoveEnemyTowards(t_TwoDArray arrGame, int intRows, int intCols, int intRow, int intCol, int intPRow, int intPCol)
    {
        int intDRow = intRow;
        int intDCol = intCol;

        if(intPCol < intCol)
            intDCol--;
        if(intPCol > intCol)
            intDCol++;

        if(intPRow < intRow)
            intDRow--;
        if(intPRow > intRow)
            intDRow++;

        if(IsInWorld(intRows, intCols, intDRow, intDCol))
        {
            arrGame[intDRow][intDCol] = arrGame[intDRow][intDCol] + ENEMY;
            arrGame[intRow][intCol] = arrGame[intRow][intCol] - ENEMY;
        }
    }

    void MoveEnemy(t_TwoDArray arrGame, int intRows, int intCols)
    {
        //1. Get Current location
        int intRow = 0;
        int intCol = 0;
        if(!FindFeature(arrGame, intRows, intCols, intRow, intCol, ENEMY))
        {
            if(!FindFeature(arrGame, intRows, intCols, intRow, intCol, ENEMY_MAGIC))
                return;
        }
        //2. Calculate Destination
        //3. If in world

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
