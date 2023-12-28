/*
Tutorial code by Dr Jaco du Toit
Date: 2022/03/15
*/

#include <iostream>
#include <cstdlib>                                  //system and time functions
#include <vector>                                   //Used for the vector type
#include <ctime>                                    //Used for the time function
#include <algorithm>                                //Used for the sort function

using namespace std;

void Pause();                                       //Pause the program
void OutputVector(vector<int> vecNums);             //Outputs a vector of numbers
vector<int> GenNums();                              //Generates a vector of n-random numbers
int GenRand(int intLowest,int intHighest);          //Generates one random number
void GetOpt3(vector<int> vecNums);                  //Runs option 3
void Sort(vector<int>& vecNums);                    //Sorts a vector from lowest to highest
vector<int> GetMode(vector<int> vecNums);           //Returns a vector that contains the mode of a set of numbers
vector<int> MakeUnique(vector<int> vecNums);        //Returns a vector of unique numbers
vector<int> MakeCount(vector<int> vecUnique,vector<int> vecNums); //Returns a vector indicating the fequency of numbers in a set
int GetHighest(vector<int> vecNums);                //Returns the highest number

int main()
{
    srand(time(0));                                 //Seeds the random number generator with the current time
    bool blnContinue = true;
    char chInput = '\0';
    vector<int> vecNums;                            //Vector of numbers that will be used in the program

    do
    {
        //Menu prompt
        system("cls");
        cout << "1) Generate n random numbers" << endl
             << "2) Output the list of numbers" << endl
             << "3) Output the mode and highest number" << endl
             << "4) Quit the application" << endl;
        cin >> chInput;
        switch(chInput)
        {
            case '1':
            {
                vecNums.clear();                    //Clears the existing vector
                vecNums = GenNums();                //Generate a new set of random numbers
                break;
            }
            case '2':
            {
                OutputVector(vecNums);              //Outputs the numbers
                break;
            }
            case '3':
            {
                GetOpt3(vecNums);                   //Runs option 3
                break;
            }
            case '4':
            {
                blnContinue = false;
                break;
            }
            default:
                cerr << "Please select a valid option (1-4)" << endl;
        }
        //Pause the screen
        Pause();
    }while(blnContinue);
    return 0;
}

//Pauses the program
void Pause()
{
   cin.ignore(100,'\n') ;
   cout << "Press Enter to continue" << endl;
   cin.get();
}

/*
Outputs the vector of numbers
Arguments: A vector<int>
Returns: None
*/
void OutputVector(vector<int> vecNums)
{
    for(int n:vecNums)
    {
        cout << n << " ";
    }
    cout << endl;
}

/*
Generates a set of random numbers and stores it in a vector
Arguments: None
Returns: vector<int>
*/
vector<int> GenNums()
{
    vector<int> vecNums;
    cout << "How many random numbers:";
    int intCount =0;
    cin >> intCount;

    int intLowest = 0;
    cout << "What is the lowest random number to be generated:";
    cin >> intLowest;

    int intHighest = 0;
    cout << "What is the highest value random number to be generated:";
    cin >> intHighest;

    for(int n=0;n<intCount;n++)
    {
        int intNum = GenRand(intLowest,intHighest);
        vecNums.push_back(intNum);
    }
    return vecNums;
}

/*
Generates a random number between a lowest number and a highest number
Arguments: int intLowest, int intHighest (The two numbers representing the boundary of the numbers)
Returns: int (The random number within intLowest and intHighest range)
*/
int GenRand(int intLowest,int intHighest)
{
    int intRange = intHighest - intLowest + 1;
    int intNum = rand()%intRange;
    intNum = intNum + intLowest;

    return intNum;
}

/*
Runs Option 3
Arguments: A vector<int>
Returns: None
*/
void GetOpt3(vector<int> vecNums)
{
    vector<int> vecMode = GetMode(vecNums);
    cout << "The mode for the numbers are:" << endl;
    OutputVector(vecMode);
    cout << "The highest number in the list is:" << GetHighest(vecNums) << endl;
}

/*
Sorts the original vector.  Uses pass-by reference
Arguments: Reference to vector<int>
Returns: None
*/
void Sort(vector<int>& vecNums)
{
    sort(vecNums.begin(),vecNums.end());
}

/*
Generates the mode of a set of numbers
Arguments: A vector<int> The original set of numbers
Returns: vector<int>  The mode of numbers
*/
vector<int> GetMode(vector<int> vecNums)
{
    //A lot of debugging code has been remarked
    vector<int> vecMode;                //The vector that wil store the mode
    //Sort our list of number
    Sort(vecNums);                      //Sort the numbers in the list.  Makes it easier to calculate the mode
    //cout << "Sorted list:" << endl;
    //OutputVector(vecNums);
    //
    vector<int> vecUnique = MakeUnique(vecNums);  //Removes all the duplicate numbers in the list
    //cout << "Unique vector:" << endl;
    //OutputVector(vecUnique);

    vector<int> vecCount = MakeCount(vecUnique, vecNums);  //Count each unique number in the original list
    //cout << "Count vector:" << endl;
    //OutputVector(vecCount);

    int intHighest(GetHighest(vecCount));           //The highest number of occuring values are the modes
    //cout << "The highest count was:" << intHighest << endl;
    int intIterator = 0;
    //Iterate through each count (fequency).  If they are the highest, add the corresponding unique value, since that will be the mode
    for(int n:vecCount)
    {
        if(n==intHighest)
        {
            vecMode.push_back(vecUnique[intIterator]);
        }
        intIterator++;
    }

    return vecMode;
}

/*
Remove duplicate values from vecNums and returns only a unique set of numbers
Arguments: A vector<int>.  The original list of numbers
Returns: vector<int>.  The list with all the duplicates removed
*/
vector<int> MakeUnique(vector<int> vecNums)
{
    vector<int> vecUnique;
    Sort(vecNums);                      //We sort the numbers first to help  identify unique numbers
    int intPrev = vecNums[0];           //The first number is the first unique number
    vecUnique.push_back(intPrev);       //Add the first number to the list
    for(int n:vecNums)
    {
        if(intPrev != n)                //For each other number see if it is already in the list, if not add it.
        {
            vecUnique.push_back(n);     //Add the new number to the list
            intPrev = n;                //Take note of the new number
        }
    }

    return vecUnique;
}

/*
Sorts a list and returns the last number in the list, which will be the highest number
Arguments: A vector<int>. The original list
Returns: int. The highest valued number.
*/
int GetHighest(vector<int> vecNums)
{
    Sort(vecNums);
    return vecNums[vecNums.size()-1];
}

/*
Counts the frequency (occurence) of a specific number in a set
Arguments: vector<int>. The original set
           int. The number to determine its fequency
Returns: int. The frequency of the number as it occurs.
*/
int CountNum(vector<int> vecNums, int intNum)
{
    int intSum = 0;

    for(int n:vecNums)
    {
        if(intNum == n)
            intSum++;
    }

    return intSum;
}

/*
Returns a list a fequency list of unique numbers from an original list
Arguments: vector<int>. The unique list of numbers
           vector<int>. The original list of number
Returns: A frequency list indicating the occurences of each unique number in the list.
*/
vector<int> MakeCount(vector<int> vecUnique,vector<int> vecNums)
{
    vector<int> vecCount;
    for(int n:vecUnique)
    {
        int intCount = CountNum(vecNums,n);
        vecCount.push_back(intCount);
    }

    return vecCount;
}
