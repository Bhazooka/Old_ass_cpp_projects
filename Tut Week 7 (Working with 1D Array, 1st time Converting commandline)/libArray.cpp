#include "libArray.h"

namespace ArraySpace
{
    int GetRand(int intLower, int intUpper)
    {
        int intRange = intUpper - intLower;
        return rand()%intRange + intLower;
    }


    int ConvertToInt(string strNum) //This is used to convert strings in the argument to integers. The arguments are strings by default. Do not use atoi because it's risky. When atoi doesnt succesfully convert, it takes the value as it is and does nothing. Imagine giving a string in the argument instead of a number, according to sir, atoi might not give you an error, but will just take that string and do funky stuff.
    {
        int intNum = 0;
        stringstream ss {strNum}; //idk what string stream does. 2. in the {} you have to enter a variable of string datatype
        ss >> intNum;

        if (ss.fail())
        {
            cerr << endl << "Couldnt convert " << strNum << " to integer" << endl;
            exit(ERR_CONV);
        }

        return intNum;
    }

    bool RangeCheck(int intNum, int intLow, int IntUpper) //This function checks that the number you input is bigger than Lower bound and smaller than upper bound
    {
        //cout << "intNum: " << intNum << endl;
        //cout << "intLower: " << intLow << endl;
        //cout << "intUpper: " << IntUpper << endl;
        //cout << "Evaluate:" << (intNum >= intLow && intNum <= IntUpper) << endl;
        return (intNum >= intLow && intNum <= IntUpper); //this is a boolean expression
    }

    TypeArray AllocMem(int intCount)    //The prameter (int intCount) takes in the value of the number of items that we're going to create
    {
        TypeArray arrNums;              //This creates our array
        arrNums = new int[intCount];    //This allocates memory for the array

        for (int n=0; n<intCount;n++)   //The code in this for loop initialises all to 0 values
        {
            arrNums[n] = 0;
        }
        return arrNums;
    }

    void InitArray(TypeArray arrNums, int intCount, int intLow, int intHigh)    //Function to Initialise the (array call arrNums || number of slots (WILL BE USED TO for loop from the number n to intCount, to enter a value between each array slot) || insert a random value >= Lower bound || <= than upper bound)
    {
        for(int n=0; n<intCount; n++)               //This initializes each array slot in the array to a random value between Lower bound and upper bound
        {
            arrNums[n]= GetRand(intLow, intHigh);
        }
    }

    void PrintArray(TypeArray arrNums, int intCount) //Function to display (array called arrNums || the number of items (or slots) in the array (intCount) that we'll use to loop through), notice that this function is only displaying stuff so we dont need more parameters, just the
        for(int n=0; n<intCount; n++)
        {
            cout << arrNums[n] << " ";
        }
        cout << endl;
    }

    void CopyArray(TypeArray arrFrom, TypeArray arrTo, int intCount)
    {
        for(int n=0; n<intCount; n++)
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
        for (int n=0; n<intCount; n++)
        {
            int f_min_1 = 0;
            int f_plus_1 =0;
            if (n==0)
                f_min_1 = arrNums[intCount-1];
            else
                f_min_1 = arrNums[n-1];

            if (n==intCount-1)
                f_plus_1 = arrNums[0];
            else
                f_plus_1 = arrNums[n+1];

            int intAbs = abs(f_min_1 - f_plus_1);

            if(intAbs==0)
                intAbs = 1;

                arrTemp[n] = arrNums[n]%intAbs;


        }
        //Copy the temp array into the original array
        CopyArray(arrTemp, arrNums, intCount); //This means copy from the temp array into nums array
        Dealloc(arrTemp); //If we dont do this, everytime we run this function, it will add more and more memory to the computer and eventually the computer will run out of memory and error.
    }


}
