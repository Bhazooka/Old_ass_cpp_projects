#ifndef LIBARRAY_H
#define LIBARRAY_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>

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
    
    typedef int* TypeArray;
    
    int ConvertToInt(string strNum);
    bool RangeCheck(int intNum, int intLow, int intUpper);
    TypeArray AllocMem(int intCount);
    void InitArray(TypeArray arrNums, int intCount, int intLow, int intHigh);
    void PrintArray(TypeArray arrNums, int intCount);
    void ModifyArray(TypeArray arrNums, int intCount);
    void Dealloc(TypeArray& arrNums);
    
}


#endif