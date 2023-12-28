#include "libInfest.h"

namespace ParkSpace
{
    int StringToInt(string strNum)
    {
        int intNum;
        stringstream ss {strNum};
        ss >> intNum;
        if(ss.fail())
        {
            cerr  << "Could not convert string to int" << endl;
            exit(ERR_CONV);
        }

        return intNum;
    }

    void RangeCheck(int intNum, int intLow, int intHigh)
    {
        bool blnInRange = true;
        if(intNum < intLow)
        {
            cerr << intNum << " was less than " << intLow << endl;
            exit(ERR_RANGE);
        }

        if(intNum > intHigh)
        {
            cerr << intNum << " was more than " << intHigh << endl;
            exit(ERR_RANGE);
        }
    }

    tTwoArray AllocMem(int intRows, int intCols)
    {
        tTwoArray arrVal = new tOneArray[intRows];
        for(int r=0;r<intRows;r++)
        {
            arrVal[r] = new int[intCols];
            for(int c=0;c<intCols;c++)
            {
                arrVal[r][c] = 0;
            }
        }

        return arrVal;
    }

    int GetRandom(int intLow, int intHigh)
    {
        assert(intLow<=intHigh);
        int intRange = intHigh-intLow+1;
        return rand()%intRange + intLow;
    }

    void PlaceFeature(tWorld stcWorld, int intSCol, int intECol, int intCount, int intFeature, int intTArray, int& intRow, int& intCol)
    {
        tTwoArray arrPlace = stcWorld.arrTree;
        if(intTArray == GRASS)
            arrPlace = stcWorld.arrGrass;
        //Place n number of items
        for(int n=0;n<intCount;n++)
        {
            intRow = GetRandom(0,stcWorld.intRows-1);
            intCol = GetRandom(intSCol-1, intECol-1);
            while(arrPlace[intRow][intCol]!=0)
            {
                intRow = GetRandom(0,stcWorld.intRows-1);
                intCol = GetRandom(intSCol-1, intECol-1);
            }
            arrPlace[intRow][intCol] = intFeature;
        }
    }

    tWorld InitWorld(int intRows, int intCols, int intTrees, int intBlue)
    {
        tWorld stcWorld;
        stcWorld.arrTree = AllocMem(intRows,intCols);
        stcWorld.arrGrass = AllocMem(intRows,intCols);
        stcWorld.intRows = intRows;
        stcWorld.intCols = intCols;
        stcWorld.intPRow = 0;
        stcWorld.intPCol = 0;
        stcWorld.enState = RUNNING;
        stcWorld.strEndMessage = "";

        int intRow = 0;
        int intCol = 0;
        //Place the player
        PlaceFeature(stcWorld, 1, 2, 1, PLAYER, TREE, stcWorld.intPRow, stcWorld.intPCol);

        //Place the blue grass
        PlaceFeature(stcWorld, 1, stcWorld.intCols, intBlue, BLUE, GRASS, intRow, intCol);

        //Place heathly trees
        PlaceFeature(stcWorld, 1, stcWorld.intCols, intTrees*.75, HEALTH_HIGH, TREE, intRow, intCol);

        //Place sick trees
        PlaceFeature(stcWorld, 1, stcWorld.intCols, intTrees*.25, SICK_HIGH, TREE, intRow, intCol);

        return stcWorld;
    }

    void PrintWorld(tWorld stcWorld)
    {
        system("cls");
        for(int r=0;r<stcWorld.intRows;r++)
        {
            for(int c=0;c<stcWorld.intCols;c++)
            {
                if(r==stcWorld.intPRow && c==stcWorld.intPCol)
                    cout << CH_PLAYER;
                else if(stcWorld.arrTree[r][c] >= SICK_LOW && stcWorld.arrTree[r][c] <= SICK_HIGH)
                {
                    if(stcWorld.arrGrass[r][c] == BLUE)
                        cout << CH_TREE_S_B;
                    else
                        cout << CH_TREE_S;
                }
                else if(stcWorld.arrTree[r][c] >= HEALTH_LOW && stcWorld.arrTree[r][c] <= HEALTH_HIGH)
                {
                    if(stcWorld.arrGrass[r][c] == BLUE)
                        cout << CH_TREE_H_B;
                    else
                        cout << CH_TREE_H;
                }
                else if(stcWorld.arrTree[r][c] == SICK_DEAD)
                {
                    if(stcWorld.arrGrass[r][c] == BLUE)
                        cout << CH_TREE_S_B;
                        //cout << CH_TREE_DEAD;
                    else
                        cout << CH_TREE_S;
                        //cout << CH_TREE_DEAD;
                }
                else if(stcWorld.arrTree[r][c] == HEALTH_DEAD)
                {
                    if(stcWorld.arrGrass[r][c] == BLUE)
                        cout << CH_TREE_H_B;
                        //cout << CH_TREE_DEAD;
                    else
                        cout << CH_TREE_H;
                        //cout << CH_TREE_DEAD;
                }
                else if(stcWorld.arrGrass[r][c] == BLUE)
                    cout << CH_BLUE;
                else
                    cout << CH_LAWN;
                cout << " ";
            }
            cout << endl;
        }
        cout << "w: Move up \t\te:Move up+right \td:Move right" << endl
             << "c: Move down+right \tx:Move down \t\tz:Move down+left" << endl
             << "a: Move left \t\tq:Move up+left" << endl
             << "m: Quit" << endl;
    }

    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to continue" << endl;
        cin.get();
    }

    bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        return (intRow>=0 && intRow<intRows &&
                intCol>=0 && intCol<intCols);
    }

    void ClearBlue(tWorld& stcWorld, int intRow, int intCol)
    {
        if(stcWorld.arrGrass[intRow][intCol]==BLUE)
        {
            stcWorld.arrGrass[intRow][intCol] = LAWN;
        }
    }

    void MovePlayer(tWorld& stcWorld, char chInput)
    {
        int intDRow = stcWorld.intPRow;
        int intDCol = stcWorld.intPCol;
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
        if(IsInWorld(stcWorld.intRows, stcWorld.intCols, intDRow, intDCol))
        {
            //Where we try to move into a healthy tree
            if(stcWorld.arrTree[intDRow][intDCol] >= HEALTH_LOW &&
               stcWorld.arrTree[intDRow][intDCol] <= HEALTH_HIGH)
            {
                //If there is a blue grass in the healthy tree location
                ClearBlue(stcWorld, intDRow, intDCol);
                return;
            }

            //Where we try to move into a sick tree
            if(stcWorld.arrTree[intDRow][intDCol] >= SICK_LOW &&
               stcWorld.arrTree[intDRow][intDCol] <= SICK_HIGH)
            {
                stcWorld.arrTree[intDRow][intDCol]+=10;
                //If there is a blue grass in the healthy tree location
                ClearBlue(stcWorld, intDRow, intDCol);
                return;
            }

            //If the destination contains a dead tree
            if(stcWorld.arrTree[intDRow][intDCol] >= SICK_DEAD)
            {
                //If there is a blue grass in the healthy tree location
                stcWorld.arrTree[intDRow][intDCol]  = HEALTH_DEAD;
                ClearBlue(stcWorld, intDRow, intDCol);
                return;
            }

            stcWorld.intPRow = intDRow;
            stcWorld.intPCol = intDCol;
            stcWorld.arrTree[intDRow][intDCol] = PLAYER;
            ClearBlue(stcWorld, intDRow, intDCol);
        }

    }

    void CopyArray(tTwoArray arrFrom, tTwoArray arrTo, int intRows, int intCols)
    {
        for(int r=0;r<intRows;r++)
        {
            for(int c=0;c<intCols;c++)
            {
                arrTo[r][c] = arrFrom[r][c];
            }
        }
    }

    void Dealloc(tTwoArray& arrVal, int intRows)
    {
        assert(arrVal!=nullptr);
        for(int r=0;r<intRows;r++)
            delete[] arrVal[r];
        delete[] arrVal;
        arrVal = nullptr;
    }

    int CountTree(tWorld stcWorld, int intRow, int intCol)
    {
        int intCount =0;
        if(IsInWorld(stcWorld.intRows, stcWorld.intCols,intRow-1,intCol))
        {
            if(stcWorld.arrTree[intRow-1][intCol]>=SICK_LOW &&
               stcWorld.arrTree[intRow-1][intCol]<=SICK_HIGH)
                intCount++;
            if(stcWorld.arrTree[intRow-1][intCol]==SICK_DEAD)
                intCount++;
        }
        if(IsInWorld(stcWorld.intRows, stcWorld.intCols,intRow,intCol-1))
        {
            if(stcWorld.arrTree[intRow][intCol-1]>=SICK_LOW &&
               stcWorld.arrTree[intRow][intCol-1]<=SICK_HIGH)
                intCount++;
            if(stcWorld.arrTree[intRow][intCol-1]==SICK_DEAD)
                intCount++;
        }
        if(IsInWorld(stcWorld.intRows, stcWorld.intCols,intRow,intCol+1))
        {
            if(stcWorld.arrTree[intRow][intCol+1]>=SICK_LOW &&
               stcWorld.arrTree[intRow][intCol+1]<=SICK_HIGH)
                intCount++;
            if(stcWorld.arrTree[intRow][intCol+1]==SICK_DEAD)
                intCount++;
        }
        if(IsInWorld(stcWorld.intRows, stcWorld.intCols,intRow+1,intCol))
        {
            if(stcWorld.arrTree[intRow+1][intCol]>=SICK_LOW &&
               stcWorld.arrTree[intRow+1][intCol]<=SICK_HIGH)
                intCount++;
            if(stcWorld.arrTree[intRow+1][intCol]==SICK_DEAD)
                intCount++;
        }
        return intCount;
    }

    int CountLawn(tWorld stcWorld, int intRow, int intCol)
    {
        int intCount = 0;

        for(int r=intRow-1;r<=intRow+1;r++)
        {
            for(int c=intCol-1;c<=intCol+1;c++)
            {
                if(r==intRow && c==intCol)
                    continue;
                else
                {
                    if(IsInWorld(stcWorld.intRows, stcWorld.intCols,r,c))
                    {
                        if(stcWorld.arrGrass[r][c]==BLUE)
                            intCount++;
                    }
                }
            }
        }

        return intCount;
    }

    void UpdateWorld(tWorld& stcWorld)
    {
        tTwoArray arrTGrass = AllocMem(stcWorld.intRows, stcWorld.intCols);
        tTwoArray arrTTree = AllocMem(stcWorld.intRows, stcWorld.intCols);
        bool blnUpdatedTemp = false;
        for(int r=0;r<stcWorld.intRows;r++)
        {
            for(int c=0;c<stcWorld.intCols;c++)
            {
                //Growing of grass
                if(stcWorld.arrGrass[r][c] == LAWN)
                {
                    //count blue grass
                    int intBlue = CountLawn(stcWorld, r, c);
                    //update the array
                    intBlue = intBlue * 5;
                    int intChance = GetRandom(1,100);
                    if(intChance<=intBlue)
                       arrTGrass[r][c] = BLUE;
                    else
                        arrTGrass[r][c] = LAWN;


                }

                if(stcWorld.arrGrass[r][c] == BLUE)
                    arrTGrass[r][c] = BLUE;

                //Tree infection
                if(stcWorld.arrTree[r][c] >= HEALTH_LOW &&
                   stcWorld.arrTree[r][c] <= HEALTH_HIGH)
                {
                    int intCount = CountTree(stcWorld, r, c);
                    if(intCount > 0)
                    {
                        int intChance = GetRandom(1,100);
                        if(intChance<=25)
                        {
                            arrTTree[r][c] = stcWorld.arrTree[r][c]-10;
                            if(arrTTree[r][c] ==0)
                                arrTTree[r][c] = SICK_DEAD;
                        }
                    }
                    else
                        arrTTree[r][c] = stcWorld.arrTree[r][c];
                }

                if(stcWorld.arrTree[r][c] == HEALTH_DEAD)
                {
                    int intCount = CountTree(stcWorld, r, c);
                    if(intCount > 0)
                    {
                        int intChance = GetRandom(1,100);
                        if(intChance<=25)
                        {
                            arrTTree[r][c] = SICK_DEAD;
                        }
                    }
                    else
                        arrTTree[r][c] = HEALTH_DEAD;
                }
                //If it is is dead then it stays dead.
                if(stcWorld.arrTree[r][c] == SICK_DEAD)
                    arrTTree[r][c] = stcWorld.arrTree[r][c];

                //If it is already sick then deplete health
                if(stcWorld.arrTree[r][c] >= SICK_LOW &&
                   stcWorld.arrTree[r][c] <= SICK_HIGH)
                {
                    arrTTree[r][c] = stcWorld.arrTree[r][c] - 1;
                    if(arrTTree[r][c] ==0)
                        arrTTree[r][c] = SICK_DEAD;
                }

                //Copy the player
                if(stcWorld.arrTree[r][c] == PLAYER)
                    arrTTree[r][c] = PLAYER;

            }
        }


        CopyArray(arrTTree, stcWorld.arrTree, stcWorld.intRows, stcWorld.intCols);
        CopyArray(arrTGrass, stcWorld.arrGrass, stcWorld.intRows, stcWorld.intCols);
        Dealloc(arrTGrass, stcWorld.intRows);
        Dealloc(arrTTree, stcWorld.intCols);
    }

    void CheckEnd(tWorld& stcWorld)
    {
        int intCountSick = 0;
        int intCountBlue = 0;
        int intCountDead = 0;
        int intCountHealth = 0;

        for(int r=0;r<stcWorld.intRows;r++)
        {
            for(int c=0;c<stcWorld.intCols;c++)
            {
                if(stcWorld.arrTree[r][c] >= SICK_LOW &&
                   stcWorld.arrTree[r][c] <= SICK_HIGH)
                    intCountSick++;

                if(stcWorld.arrTree[r][c] >= HEALTH_LOW &&
                   stcWorld.arrTree[r][c] <= HEALTH_HIGH)
                    intCountHealth++;

                if(stcWorld.arrTree[r][c]==SICK_DEAD)
                {
                    intCountDead++;
                    intCountSick++;
                }

                if(stcWorld.arrTree[r][c]==HEALTH_DEAD)
                {
                    intCountDead++;
                }

                if(stcWorld.arrGrass[r][c] == BLUE)
                    intCountBlue++;
            }
        }

        //If there are no sick trees then
        if(intCountSick==0 && intCountHealth==0 && intCountDead > 0)
        {
            stcWorld.enState = LOST;
            stcWorld.strEndMessage = "All the trees died";
        }

        //See if the 75% of the world is filled with blue grass
        int intMajorVal = .75*(stcWorld.intRows * stcWorld.intCols);
        if(intCountBlue >=intMajorVal)
        {
            stcWorld.enState = LOST;
            stcWorld.strEndMessage = "The blue grass infested everything";
        }

        //See if there are no infested trees and no blue grass
        if(intCountSick==0 && intCountBlue==0)
        {
            stcWorld.enState = WON;
            stcWorld.strEndMessage = "The infestation was cleared.";
        }


    }

}
