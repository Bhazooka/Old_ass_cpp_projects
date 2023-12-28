#include "libPark.h"

namespace ParkSpace
{
    int ConvertToInt(string strNum)
    {
        int intNum;
        stringstream ss{strNum};
        ss >> intNum;
        if(ss.fail())
        {
            cerr << "Couldn't convert string arguments to integer";
            exit(ERR_CONV);
        }
        return intNum;
    }

    int GenRand(int intLow, int intHigh)
    {
        int intRange = intHigh - intLow + 1;
        return rand()%intRange + intLow;
    }

    void RangeCheck(int intValue, int intLow, int intHigh)
    {
        if(intValue < intLow || intValue > intHigh)
        {
            cerr << "The value entered should be less than " << intHigh << ", and greater than " << intLow;
            exit(ERR_RANGE);
        }
    }

    twoDarr AllocMem(int intRows, int intCols)
    {
        twoDarr arrWorld;
        arrWorld = new oneDarr[intCols];
        for (int r=0; r<intRows; r++)
        {
            arrWorld[r]= new int[intCols];
            for (int c=0; c<intCols; c++)
            {
                arrWorld[r][c] = LAWN;
            }
        }
        return arrWorld;
    }

    void PlaceObjects(recWorld& stcWorld, int intAmount, int intObject, int& intRow, int& intCol)
    {
        assert(stcWorld.arrWorld!=nullptr);
        for (int a=0; a<intAmount; a++)
        {
            intRow = GenRand(0, stcWorld.intRows-1);
            intCol = GenRand(0, stcWorld.intCols-1);
            while(stcWorld.arrWorld[intRow][intCol] != LAWN)
            {
                intRow = GenRand(0, stcWorld.intRows-1);
                intCol = GenRand(0, stcWorld.intCols-1);
            }
            stcWorld.arrWorld[intRow][intCol] = intObject;
        }
    }

    recWorld InitWorld(int intRows, int intCols, int intTrees, int intI_Trees, int intBlueGrass)
    {
        recWorld stcWorld;

        stcWorld.arrWorld = AllocMem(intRows, intCols);
        stcWorld.intRows = intRows;
        stcWorld.intCols = intCols;

        stcWorld.intTrees = intTrees;
        stcWorld.intI_Trees = intI_Trees;
        stcWorld.intBlueGrass = intBlueGrass;
        stcWorld.GameStatus = RUNNING;

        int WorldArea = intRows * intCols;
        int TotalObjects = intTrees + intI_Trees + intBlueGrass;
        if(WorldArea <= TotalObjects)
        {
            cerr << "Theres not enough space in the world to fit all the objects.";
            exit(ERR_SPACE);
        }

        int intRow = 0;
        int intCol = 0;

        //Place the objects
        PlaceObjects(stcWorld, intTrees, TREE, intRow, intCol);
        PlaceObjects(stcWorld, intI_Trees, I_TREE, intRow, intCol);
        PlaceObjects(stcWorld, intBlueGrass, BLUEGRASS, intRow, intCol);


        int intPCol = GenRand(0,1);
        //The player can only spawn in the second of first col
        PlaceObjects(stcWorld, 1, PLAYER, intRow, intPCol);
        stcWorld.PlayerRow = intRow;
        stcWorld.PlayerCol = intCol;

        return stcWorld;
    }

    //Print the world
    void Display (recWorld stcWorld)
    {
        assert(stcWorld.arrWorld!=nullptr);
        system("cls");
        for (int r=0; r<stcWorld.intRows; r++)
        {
            for (int c=0; c<stcWorld.intCols; c++)
            {
                cout << OBJECTS[stcWorld.arrWorld[r][c]] << " ";
            }
            cout << endl;
        }

        cout << "w: UP" << endl
             << "e: UP+RIGHT" << endl
             << "d: RIGHT" << endl
             << "c: DOWN+RIGHT" << endl
             << "x: DOWN" << endl
             << "z: DOWN+LEFT" << endl
             << "a: LEFT" << endl
             << "q: UP+LEFT" << endl
             << "~: QUIT " << endl;
    }

    //Is in World
    bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        return (intRow >= 0 && intRow < intRows &&
                intCol >= 0 && intCol < intCols);
    }

    //MovePlayer
    void MovePlayer(recWorld& stcWorld, int Choice)
    {
        assert(stcWorld.arrWorld!=nullptr);
        int intDRow = stcWorld.PlayerRow;
        int intDCol = stcWorld.PlayerCol;

        switch(Choice) //Player movements (including diagonals)
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
            intDRow++;
            intDCol++;
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
            intDRow--;
            intDCol--;
            break;

        }

        if(IsInWorld(stcWorld.intRows, stcWorld.intCols, intDRow, intDCol))
        {
            int DObject = stcWorld.arrWorld[intDRow][intDCol];
//            if(DObject == TREE)
//            {
//                stcWorld.arrWorld[intDRow][intDCol] = TREE;
//            }
            if(DObject == I_TREE)      //If the player goes to an infected tree, it gets dis-infected
            {
                stcWorld.arrWorld[intDRow][intDCol] = TREE;
            }
            if(DObject == BLUEGRASS)   //If the player walks over infected grass, it turns into normal grass
            {
                stcWorld.arrWorld[intDRow][intDCol] = LAWN;
                stcWorld.intBlueGrass--;
            }

            if(stcWorld.arrWorld[intDRow][intDCol] == LAWN)
            {
                stcWorld.arrWorld[stcWorld.PlayerRow][stcWorld.PlayerCol] = LAWN;
                stcWorld.arrWorld[intDRow][intDCol] = PLAYER;

                stcWorld.PlayerRow = intDRow;
                stcWorld.PlayerCol = intDCol;
            }
            if(stcWorld.arrWorld[intDRow][intDCol] == TREE)
            {
                stcWorld.arrWorld[stcWorld.PlayerRow][stcWorld.PlayerCol] = TREE;
                stcWorld.arrWorld[intDRow][intDCol] = PLAYER;

                stcWorld.PlayerRow = intDRow;
                stcWorld.PlayerCol = intDCol;
            }
        }
    }

    void CheckEnd(recWorld& stcWorld)
    {
        assert(stcWorld.arrWorld!=nullptr);
        if(stcWorld.intBlueGrass == 0 && stcWorld.intI_Trees == 0)
        {
            stcWorld.GameStatus = WIN;
        }
    }
    //Deallocate
    twoDarr FreeSpace(twoDarr& arrWorld, int intRows)
    {
        assert(arrWorld!=nullptr);
        for (int r=0; r<intRows; r++)
        {
            delete[] arrWorld[r];
        }
        delete[] arrWorld;
        arrWorld = nullptr;
    }
}
