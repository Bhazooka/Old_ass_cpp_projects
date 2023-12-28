#include "libSnake.h"

namespace SnakeSpace
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

    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Press Enter to continue" << endl;
        cin.get();
    }

    t_TwoArray AllocMem(int intRows, int intCols)
    {
        t_TwoArray arrGame;
        arrGame = new t_OneArray[intRows];
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

    void PlaceFruit(tGame& stcGame)
    {
        int intRow = GetRandom(0,stcGame.intRows-1);
        int intCol = GetRandom(0,stcGame.intCols-1);
        while(stcGame.arrGame[intRow][intCol]!=EMPTY)
        {
            intRow = GetRandom(0,stcGame.intRows-1);
            intCol = GetRandom(0,stcGame.intCols-1);
        }
        stcGame.arrGame[intRow][intCol]=FRUIT;
    }

    tGame InitGame(int intRows, int intCols)
    {
        tGame stcGame;
        stcGame.arrGame = AllocMem(intRows, intCols);
        stcGame.intRows = intRows;
        stcGame.intCols = intCols;

        stcGame.intPRow = GetRandom(0,intRows-1);
        stcGame.intPCol = GetRandom(0,intCols-1);
        stcGame.intScore = 0;
        stcGame.intLength = 0;
        stcGame.enStatus = RUNNING;

        //Place the snake head in the array
        stcGame.arrGame[stcGame.intPRow][stcGame.intPCol] = HEAD;
        //Place the fruit in the array
        PlaceFruit(stcGame);

        return stcGame;
    }

    bool IsBodyOfSnake(tGame stcGame, int intRow, int intCol)
    {
        if(stcGame.arrGame[intRow][intCol] >=BODY_START &&
           stcGame.arrGame[intRow][intCol] <=BODY_END)
           return true;

        return false;
    }

    void PrintWorld(tGame stcGame)
    {
        system("clear");
        for(int r=0;r<stcGame.intRows;r++)
        {
            for(int c=0;c<stcGame.intCols;c++)
            {
                switch(stcGame.arrGame[r][c])
                {
                    case HEAD:
                        cout << CH_HEAD;
                        break;
                    case FRUIT:
                        cout << CH_FRUIT;
                        break;
                    case EMPTY:
                        cout << CH_EMPTY;
                        break;
                    default:
                        cout << CH_BODY;
                }
                cout << " ";
            }
            cout << endl;
        }
        cout << "w: Move up" << endl
             << "s: Move down" << endl
             << "a: Move left" << endl
             << "d: Move right" << endl
             << "q: Quit" << endl
             << "Score:" << stcGame.intScore << endl;
    }

    bool IsInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        if(intRow<0) return false;
        if(intCol<0) return false;
        if(intRow>=intRows) return false;
        if(intCol>=intCols) return false;
        return true;
    }



    void MoveHead(tGame& stcGame, int intDRow, int intDCol)
    {
        //See if we die
        if(IsBodyOfSnake(stcGame, intDRow, intDCol))
        {
            stcGame.enStatus = LOST;
            return;
        }

        stcGame.arrGame[intDRow][intDCol] = HEAD;
        stcGame.arrGame[stcGame.intPRow][stcGame.intPCol] = stcGame.intLength;
        stcGame.intPRow = intDRow;
        stcGame.intPCol = intDCol;
    }

    void MoveBody(tGame& stcGame)
    {
        for(int r=0;r<stcGame.intRows;r++)
        {
            for(int c=0;c<stcGame.intCols;c++)
            {
                if(IsBodyOfSnake(stcGame, r, c))
                    stcGame.arrGame[r][c]--;
            }
        }
    }

    void MoveSnake(tGame& stcGame, int intDirection)
    {
        int intDRow = stcGame.intPRow;
        int intDCol = stcGame.intPCol;
        switch(intDirection)
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


        if(IsInWorld(stcGame.intRows,stcGame.intCols, intDRow, intDCol))
        {
            //Handle the case where we eat
            if(stcGame.arrGame[intDRow][intDCol]==FRUIT)
            {
                //Move the head
                stcGame.intLength++;
                stcGame.intScore++;
                MoveHead(stcGame, intDRow, intDCol);
                //Create new Fruit
                PlaceFruit(stcGame);
            }
            else
            {
                //Move the body
                MoveBody(stcGame);
                //Move the head
                MoveHead(stcGame, intDRow, intDCol);
            }

        }

    }

    void Dealloc(t_TwoArray& arrGame, int intRows)
    {
        for(int r=0;r<intRows;r++)
            delete[] arrGame[r];
        delete[] arrGame;
        arrGame = nullptr;
    }


}
