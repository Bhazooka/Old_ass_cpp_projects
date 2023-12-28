#include "libArray.h"
#include <iostream>

using namespace std;
using namespace ArraySpace;

int main(int argc, char** argv) //argc (arrgument count): counts the number of arrguments. in codebloacks, you can set your arguments in the toolbar Go to 1."Project" -> look for 2."Set progras' argument" || char** declares an array of string, it is typically called argv (arrgument vector). Char* declares a cstring ||
{
    //seed the random number generator
    srand(time(nullptr)); //Time function usually takes 0, nullptr means nothing, empty


    //Section to discribe number of command line arguments, for now we expect a number of 4 arguments. the first argument is automatic (done by the computer), so we just need to input 3 arguments
    cout << "The number of arguments: " << argc << endl;
    for (int n = 0; n < argc; n++)
    {
        cout << "Arrgument " << n << " is: " << argv[n] << endl;
    }

    //check for the expected number of arrguments
    if (argc!=4)
    {
        cerr << endl << "Please run the application with " << argv[0] <<"<TotalItems> <LowestRandNum> <HighestRandNum>" << endl;
        exit(ERR_ARGC);
    }

    //Convert string arguments into integers. All these arguments are all strings types at the moment. we have to convert that into interger types
    //(The arguments that we entered are 20 2 30 but they are stored as strings for the while)
    //We are converting the arguments into integers
    int intCount = ConvertToInt(argv[1]); //Our first argument 20, becomes our count for the number of values we want in our random numbers
    int intLower = ConvertToInt(argv[2]); //Second argument 2, becomes our lower bound
    int intUpper = ConvertToInt(argv[3]); //Third argument 30, becomes our upper bound


    //Range checking
    if(!RangeCheck(intCount, MIN_COUNT, MAX_COUNT)) //The rangeCheck function that we created checks that intCount is >= (MIN_COUNT which is 5) and <= (MAX_COUNT which is 30)
    {
        cerr << "Please make sure the total number of random numbers is at least " << MIN_COUNT
        << ", and at most " << MAX_COUNT << endl;
        exit(ERR_RANGE);
    }
    if(!RangeCheck(intLower, MIN_RAND, MAX_RAND)) //checks that intLower is >= (MIN_RAND which is 0) and <= (MAX_RAND which is 30)
    {
        cerr << "Out of range: " << intLower << endl;
        exit(ERR_RANGE);
    }
    if(!RangeCheck(intUpper, intLower + 1, MAX_RAND)) //checks that intUpper is >= (intLower + 1, because it cant be the same as intLower) and <= (MAX_RAND which is 30)
    {
        cerr << "Out of range: " << intUpper << endl;
        exit(ERR_RANGE);
    }

    //declare array and allocate memory
    TypeArray arrNums = AllocMem(intCount); //in the TypeArray arrNums. = allocate memory of intCount value.
    //Initialie the array
    InitArray( arrNums, intCount, intLower, intUpper); //Initialise the (array call arrNums || for loop from the number n to intcount, to enter a value between each array slot || insert a random value >= Lower bound || <= than upper bound)

    bool blnContinue = true;
    char chInput = '\0';
    do
    {
        //Print the array
        PrintArray(arrNums, intCount);
        cout << "Press q to quit. Press Any othr key to continue" << endl;
        //Get input
        cin >> chInput;
        //Evaluate input
        switch(chInput)
        {
        case 'q':
            blnContinue = false;
            break;
        }
        //Modify the array
        ModifyArray(arrNums, intCount);
    }while(blnContinue);


    return 0;
}
