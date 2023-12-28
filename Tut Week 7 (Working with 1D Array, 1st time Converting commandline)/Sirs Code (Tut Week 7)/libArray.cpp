#include "libArray.h"

namespace ArraySpace
{
    int GetRand(int intLower, int intUpper)
    {
        int intRange = intUpper - intLower + 1;
        return rand()%intRange + intLower;
    }
    
    int ConvertToInt(string strNum)
    {
        int intNum = 0;
        stringstream ss {strNum};
        ss >> intNum;
        if(ss.fail())
        {
            cerr << "Could not convert " << strNum << " to integer" << endl;
            exit(ERR_CONV);
        }
        
        return intNum;
    }
    
    bool RangeCheck(int intNum, int intLow, int intUpper)
    {
        //cout << "intNum:" << intNum << endl;
        //cout << "intLow:" << intLow << endl;
        //cout << "intUpper:" << intUpper << endl;
        //cout << "Evaluate:" << (intNum>=intLow && intNum<=intUpper) << endl;
        return (intNum>=intLow && intNum<=intUpper);
    }
    
    TypeArray AllocMem(int intCount)
    {
        TypeArray arrNums;
        arrNums = new int[intCount];
        //Initialise it to all zero values
        for(int n=0;n<intCount;n++)
        {
            arrNums[n] = 0;
        }
        return arrNums;
    }
    
    void InitArray(TypeArray arrNums, int intCount, int intLow, int intHigh)
    {
        for(int n=0;n<intCount;n++)
        {
            arrNums[n] = GetRand(intLow, intHigh);
        }
    }
    
    void PrintArray(TypeArray arrNums, int intCount)
    {
        for(int n=0;n<intCount;n++)
        {
            cout <<  arrNums[n] << " ";
        }
        cout << endl;
    }
    
    void CopyArray(TypeArray arrFrom, TypeArray arrTo, int intCount)
    {
        for(int n=0;n<intCount;n++)
        {
            arrTo[n] = arrFrom[n];
        }
    }
    
    void Dealloc(TypeArray& arrNums)
    {
        delete[] arrNums;
        arrNums = nullptr;
    }
    
    void ModifyArray(TypeArray arrNums, int intCount)
    {
        TypeArray arrTemp = AllocMem(intCount);
        for(int n=0;n<intCount;n++)
        {
            int f_min_1 = 0;
            int f_plus_1 = 0;
            if(n==0)
                f_min_1 = arrNums[intCount-1];
            else
                f_min_1 = arrNums[n-1];
                
            if(n==intCount-1)
                f_plus_1 = arrNums[0];
            else
                f_plus_1 = arrNums[n+1];
                
            int intAbs = abs(f_min_1 - f_plus_1);
            
            if(intAbs==0)
                intAbs = 1;
                
            arrTemp[n] = arrNums[n]%intAbs;
        }
        
        //Copy the temp array into the orig array
        CopyArray(arrTemp, arrNums, intCount);
        
        Dealloc(arrTemp);
        
    }
}