#ifndef LIBARRAY_H_INCLUDED
#define LIBARRAY_H_INCLUDED

#include <iostream>
#include <cstdlib>  //This library handles stuff like random, etc
#include <ctime>    //This library handles time
#include <cmath>    //This library holds math function
#include <sstream>  //This is the library that contains stringstream

using namespace std;

namespace ArraySpace
{
    const int ERR_ARGC = -1;
    const int ERR_CONV = -2;
    const int ERR_RANGE = -3;

    const int MIN_COUNT = 5;
    const int MAX_COUNT = 30;
    const int MIN_RAND = 0;
    const int MAX_RAND = 30;

    typedef int* TypeArray;     //We use int* to create 1D array

    int ConvertToInt(string strNum);
    bool RangeCheck(int intNum, int intLow, int IntUpper);
    TypeArray AllocMem(int intCount);
    void InitArray(TypeArray arrNums, int intCount, int intLow, int intHigh); //The parameters say ( Put random numbers into arrNums ||Total number of slots to be used for forloop|| Lower bound || upper bound )
    //Initialise the (array call arrNums || incount to be use for the For Loop, to enter a value between each array slot || insert a random value >= Lower bound || <= than upper bound)

    void PrintArray (TypeArray arrNums, int intCount);
    void ModifyArray(TypeArray arrNums, int intCount);
    void CopyArray(TypeArray arrFrom, TypeArray arrTo, int intCount);
    void Dealloc(TypeArray& arrNums); // we de allocate to get rif of the original pointer variable. if you dont do this it creates a copy of the address, and we dont want that to save memory

}


#endif // LIBARRAY_H_INCLUDED
