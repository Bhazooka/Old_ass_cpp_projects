#include "libHunt.h"

namespace HuntSpace
{
    int ConvertStr(string strNum)
    {
        int intNum;
        stringstream ss {strNum};
        ss >> intNum;
        if(ss.fail())
        {
            cerr << "Could not convert string to int" << endl;
            exit(ERR_CONV);
        }

        return intNum;
    }

    tTwoDArray AllocMem(int intRows, int intCols)
    {
        tTwoDArray arrGame;
        arrGame = new tOneDArray[intRows];
        for(int r=0;r<intRows;r++)
        {
            arrGame[r] = new int[intCols];
            for(int c=0;c<intCols;c++)
                arrGame[r][c] = EMPTY;
        }

        return arrGame;
    }

    int GetRand(int intLow, int intHigh)
    {
        assert(intHigh>=intLow);
        int intRange = intHigh - intLow + 1;
        return rand()%intRange+intLow;
    }

    void PlaceAnimals(tGame& strucGame, int intCount)
    {
        for(int n=0;n<intCount;n++)
        {
            int intRow = GetRand(0,strucGame.intRows-1);
            int intCol = GetRand(0,strucGame.intCols-1);
            while(strucGame.arrGame[intRow][intCol]!=EMPTY)
            {
                intRow = GetRand(0,strucGame.intRows-1);
                intCol = GetRand(0,strucGame.intCols-1);
            }
            strucGame.arrGame[intRow][intCol] = ANIMAL;
        }
    }

    tGame InitWorld(int intRows, int intCols, int intCountAnimal, int intChanceHE, int intPRow, int intPCol)
    {
        tGame strucGame;
        strucGame.arrGame = AllocMem(intRows, intCols);
        strucGame.intRows = intRows;
        strucGame.intCols = intCols;
        strucGame.intPRow = intPRow;
        strucGame.intPCol = intPCol;
        strucGame.intKnife=0;
        strucGame.intTrap=0;
        strucGame.intCaught=0;
        strucGame.intKnifed=0;
        strucGame.enState=RUNNING;
        strucGame.intChanceHE = intChanceHE;

        strucGame.arrGame[intPRow][intPCol] = PLAYER;
        PlaceAnimals(strucGame, intCountAnimal);

        return strucGame;
    }


    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to continue" << endl;
        cin.get();
    }

    void PrintWorld(tGame strucGame)
    {
        system("cls");
        for(int r=0;r<strucGame.intRows;r++)
        {
            for(int c=0;c<strucGame.intCols;c++)
            {
                cout << FEATURES[strucGame.arrGame[r][c]] << " ";
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
             << "p: Set a trap" << endl
             << "m: Quit" << endl
             << "Number of knives:" << strucGame.intKnife
             << "\tNumber of traps:" << strucGame.intTrap << endl
             << "Animals caught:" << strucGame.intCaught
             << "\tAnimals knifed:" << strucGame.intKnifed << endl;
    }

    bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        return (intRow>=0 && intRow<intRows &&
                intCol>=0 && intCol<intCols);
    }

    //Moves the Player into a destination
    void MoveOnlyFeature(tGame& strucGame, int intDRow, int intDCol, int intFeature)
    {
        strucGame.arrGame[strucGame.intPRow][strucGame.intPCol] = EMPTY;
        strucGame.arrGame[intDRow][intDCol] = intFeature;
        strucGame.intPRow = intDRow;
        strucGame.intPCol = intDCol;
    }

    //Function that asks for a destination and places the trap in the location.
    void PlaceTrap(tGame& strucGame)
    {
        if(strucGame.intTrap>0)
        {
            cout << "Please use the direction buttons to indicate the location of the trap" << endl;
            char chInput = '\0';
            cin >> chInput;
            int intDRow = strucGame.intPRow;
            int intDCol = strucGame.intPCol;
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
            strucGame.intTrap--;
            if(IsInWorld(strucGame.intRows, strucGame.intCols, intDRow, intDCol))
            {
                //If the destination is empty, then place the TRAP;
                int intFeature = strucGame.arrGame[intDRow][intDCol];
                if(intFeature == EMPTY)
                    strucGame.arrGame[intDRow][intDCol] = TRAP;
            }

        }

    }

    void MovePlayer(tGame& strucGame, char chInput)
    {
        int intDRow = strucGame.intPRow;
        int intDCol = strucGame.intPCol;
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
            case 'p':
                //Case to place a trap
                PlaceTrap(strucGame);
                break;
        }
        if(IsInWorld(strucGame.intRows, strucGame.intCols, intDRow, intDCol))
        {
            int intFeature = strucGame.arrGame[intDRow][intDCol];
            //If destination is empty
            if(intFeature == EMPTY)
            {
                MoveOnlyFeature(strucGame,intDRow, intDCol,PLAYER);
                return;
            }
            //If destination contains animal
            if(intFeature == ANIMAL)
            {
                //See if you a knife
                if(strucGame.intKnife > 0)
                {
                    MoveOnlyFeature(strucGame,intDRow, intDCol,PLAYER);
                    strucGame.intKnife--;
                    strucGame.intKnifed++;
                }
                else
                {
                    strucGame.enState = LOSE;
                }
                return;
            }

            //If destination contains trap
            if(intFeature == TRAP)
            {
                strucGame.enState = LOSE;
                cout << "Oh no.  You ran into a trap" << endl;
                Pause();
                return;
            }

            //If destination contains hunting equipment
            if(intFeature == H_EQUIPMENT)
            {
                int intChance = GetRand(1,100);
                if(intChance<=25)
                    strucGame.intKnife++;
                else
                    strucGame.intTrap++;
                MoveOnlyFeature(strucGame,intDRow, intDCol,PLAYER);
                return;
            }
        }

    }

    void Dealloc(tTwoDArray& arrGame, int intRows)
    {
        for(int r=0;r<intRows;r++)
            delete[] arrGame[r];
        delete[] arrGame;
        arrGame = nullptr;
    }

    void CopyArray(tTwoDArray arrFrom, tTwoDArray arrTo, int intRows, int intCols)
    {
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                arrTo[r][c] = arrFrom[r][c];
            }
        }
    }

    //To make the temporary array working a bit easier.  Copy all the stationary features
    void CopyAllExceptAnimals(tTwoDArray arrFrom, tTwoDArray arrTo, int intRows, int intCols)
    {
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                if(arrFrom[r][c]!=ANIMAL)
                    arrTo[r][c] = arrFrom[r][c];
            }
        }
    }

    //Move the animal into an empty space, otherwise the animals may disappear
    void PlaceAnimal(tTwoDArray arrGame, int intRows, int intCols, int intRow, int intCol)
    {
        for(int r=intRow-1;r<=intRow+1;r++)
        {
            for(int c=intCol-1;c<=intCol+1;c++)
            {
                if(IsInWorld(intRows, intCols, r,c))
                {
                    if(arrGame[r][c]==EMPTY || arrGame[r][c]==H_EQUIPMENT)
                    {
                        arrGame[r][c] = ANIMAL;
                        return;
                    }
                }
            }
        }
    }

    //Move the animals
    void MoveAnimals(tGame& strucGame)
    {
        //We use a temp array to create the new state of the world
        tTwoDArray arrTemp = AllocMem(strucGame.intRows, strucGame.intCols);
        //Copy all the non-moving features into the temp array
        CopyAllExceptAnimals(strucGame.arrGame, arrTemp, strucGame.intRows, strucGame.intCols);
        //Find the next animal in the original array and move it.
        for(int r=0;r<strucGame.intRows;r++)
        {
            for(int c=0;c<strucGame.intCols;c++)
            {
                int intFeature = strucGame.arrGame[r][c];
                bool blnTemp = false;
                //If the feature is an animal, move the animal
                if(intFeature == ANIMAL)
                {
                    //Get a random location to move into
                    int intRMod = GetRand(-1,1);
                    int intCMod = GetRand(-1,1);
                    int intDRow = r+intRMod;
                    int intDCol = c+intCMod;
                    //Move the animal if the location is in the world otherwise place the animal in an empty space around the location
                    if(IsInWorld(strucGame.intRows, strucGame.intCols, intDRow, intDCol))
                    {
                        //Empty
                        if(arrTemp[intDRow][intDCol]==EMPTY)
                        {
                            arrTemp[intDRow][intDCol] = ANIMAL;
                            continue;
                        }

                        //Player
                        if(arrTemp[intDRow][intDCol]==PLAYER)
                        {
                            arrTemp[intDRow][intDCol] = ANIMAL;
                            cout << "Oh no.  An animal caught you" << endl;
                            Pause();
                            strucGame.enState = LOSE;
                            continue;
                        }

                        //Trap
                        if(arrTemp[intDRow][intDCol]==TRAP)
                        {
                            strucGame.intCaught++;
                            arrTemp[intDRow][intDCol] = EMPTY;
                            continue;
                        }

                        //Hunting equipment
                        if(arrTemp[intDRow][intDCol]==H_EQUIPMENT)
                        {
                            arrTemp[intDRow][intDCol] = ANIMAL;
                            continue;
                        }

                        //If destination is an animal
                        if(arrTemp[intDRow][intDCol]==ANIMAL)
                        {
                            PlaceAnimal(arrTemp,strucGame.intRows, strucGame.intCols, intDRow, intDCol);
                            continue;
                        }

                        arrTemp[r][c]=ANIMAL;
                        cout << "Not supposed to get here" << endl;
                        Pause();
                    }
                    else
                    {
                        PlaceAnimal(arrTemp,strucGame.intRows, strucGame.intCols, intDRow, intDCol);
                    }

                }
            }
        }

        //Copy the temp array into the real array
        CopyArray(arrTemp, strucGame.arrGame, strucGame.intRows, strucGame.intCols);

        //Deallocate the memory for the temp array
        Dealloc(arrTemp, strucGame.intRows);
    }

    //Update the game with hunting equipment.
    void Update(tGame& strucGame)
    {
        for(int r=0;r<strucGame.intRows;r++)
        {
            for(int c=0;c<strucGame.intCols;c++)
            {
                if(strucGame.arrGame[r][c]==EMPTY)
                {
                    int intChance = GetRand(1,100);
                    if(intChance <= strucGame.intChanceHE)
                        strucGame.arrGame[r][c]=H_EQUIPMENT;
                }
            }
        }
    }

    //See if all the animals are hunted.
    void EndGame(tGame& strucGame)
    {
        int intCount = 0;
        for(int r=0;r<strucGame.intRows;r++)
        {
            for(int c=0;c<strucGame.intCols;c++)
            {
                if(strucGame.arrGame[r][c]==ANIMAL)
                {
                    return;
                }
            }
        }
        strucGame.enState = WIN;
    }
}
