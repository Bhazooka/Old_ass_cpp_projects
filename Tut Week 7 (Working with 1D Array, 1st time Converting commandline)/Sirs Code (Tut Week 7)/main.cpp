#include "libArray.h"
#include <iostream>

using namespace std;
using namespace ArraySpace;

int main(int argc, char** argv)
{
    //Seed the rand num generator
    srand(time(nullptr));
    //Section to describe the number of command line arguments
    cout << "The number of arguments:" << argc << endl;
    for(int n=0;n<argc;n++)
    {
        cout << "Argument " << n << " is:" << argv[n] << endl;
    }
    
    //Check for the expected number of args.
    if(argc!=4)
    {
        cerr << "Please run the application with " << argv[0] << " <TotalItems> <LowestRandNum> <HighestRandNum>" << endl;
        exit(ERR_ARGC);
    }
    
    //Convert the string arguments into integers
    int intCount = ConvertToInt(argv[1]);
    int intLower = ConvertToInt(argv[2]);
    int intUpper = ConvertToInt(argv[3]);
    
    //Range checking
    if(!RangeCheck(intCount,MIN_COUNT,MAX_COUNT))
    {
        cerr << "Please make sure the total number of random number is at least " << MIN_COUNT
             << " and at most " << MAX_COUNT << endl;
        exit(ERR_RANGE);
    }
    if(!RangeCheck(intLower,MIN_RAND,MAX_RAND))
    {
        cerr << "Out of range:" << intLower << endl;
        exit(ERR_RANGE);
    }
    if(!RangeCheck(intUpper,intLower+1,MAX_RAND))
    {
        cerr << "Out of range:" << intUpper << endl;
        exit(ERR_RANGE);
    }
    
    //Declare the array and allocate mem
    TypeArray arrNums = AllocMem(intCount);
    //Initialise the array
    InitArray(arrNums, intCount, intLower, intUpper);
    
    bool blnContinue = true;
    char chInput = '\0';
    do
    {
        //Print the array
        PrintArray(arrNums, intCount);
        cout << "Press q to quit.  Any other key to continue" << endl;
        //Get intput
        cin >> chInput;
        //Evaluate input
        switch(chInput)
        {
            case 'q':
               blnContinue = false;
               break;
        }
        //Modify array
        ModifyArray(arrNums, intCount);
    }while(blnContinue);
    
    
    
    return 0;
}