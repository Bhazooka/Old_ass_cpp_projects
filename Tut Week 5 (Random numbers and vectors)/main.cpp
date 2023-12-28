#include <iostream>
#include <cstdlib>
#include <vector> //this is the library to use vectors
#include <ctime> // The library for the seed time
#include <algorithm>

using namespace std;

//Prototypes
void Pause();
void OutputVector(vector<int> vecNums);
vector <int> GenNums();
int GenRand(int intLowest, int intHighest); //this function parameters takes in 2 integers, [int lowest, int highest]
void GetOpt3(vector<int> vecNums);
void Sort(vector<int>& vecNums); //This is by value. Its indicated by the & within the parameters after the vector. We will use this function to take the sequence of random numbers generated and sort that sequence of numbers.
//by reference takes the original values being passed and changes it.
//by value takes the original value, makes a copy and tempers with the copy.
//In this case we use byRef because we want to now work with a sorted sequence of random numbers and not the original, so we had to take the original, sort it, and then use it to count the mode
vector<int> GetMode(vector<int> vecNums); //Give our vector of numbers to this function, and this will return the mode vector for us
vector<int> MakeUnique(vector<int> vecNums);
vector<int> MakeCount(vector<int> vecUnique,vector<int> vecNums);
int GetHighest(vector<int> vecNums);


int main()
{
    srand(time(0)); //this means return the time. The (0) just means return first or exact value of time. We use the srand to seed our random number generated. We are using the time to generate a random number. Computers can't generate random numbers so they rely on external factors. since time is always changing its a good candidate
    bool blnContinue = true;
    char chInput = '\0';
    vector<int> vecNums; // a vector is a list of things
    //Vector means. Construct a list <inside this list store int values> and the list name is called vecNums


    do
    {
        //Menu Prompt
        system("cls");
        cout << "1) Generate n random numbers" << endl
             << "2) Output the list of numbers" << endl
             << "3) Output the mode and the highest numbers" << endl
             << "4) Quit the application" << endl;

        cin >> chInput;
        switch(chInput)
        {
            case '1':
            {
                vecNums.clear(); //the clear function goes into vecNums and deletes every previously stored value in it
                vecNums = GenNums();
                break;
            }

            case '2':
            {
                OutputVector(vecNums);
                break;
            }

            case '3':
            {
                GetOpt3(vecNums);
                break;
            }

            case '4':
            {
                blnContinue = false;
                break;
            }

            default:
            {
                cerr << "Please select valid option between 1-4" << endl;
            }

        }
        //Pause the screen
        Pause(); // This is how you call a function

    }while(blnContinue);
    return 0;
}

//implimentation of the pause function
void Pause()
{
    cin.ignore(100, '\n');
    cout << "Press enter to continue" << endl;
    cin.get(); //The get line does the pause for us
}

void OutputVector(vector<int> vecNums)
{
    for (int n: vecNums) //for each integer in vecNums, put that integer in the variable n and output that
    {
        cout << n << " ";
    }
    cout << endl;
}

vector <int> GenNums()
{
    vector<int> vecNums;
    cout << "How many random numbers: ";
    int intCount = 0;
    cin >> intCount;

    int intLowest;
    cout << "What is the Lowest number to be generated: ";
    cin >> intLowest;

    int intHighest;
    cout << "What is the Highest number to be generated: ";
    cin >> intHighest;

    for (int n = 0; n < intCount; n++)
    {
        int intNum = GenRand(intLowest, intHighest);
        vecNums.push_back(intNum);// We use push_back to add something to our vector

    }

    return vecNums;
}

int GenRand(int intLowest, int intHighest)
{
    int intRange = intHighest - intLowest + 1;
    int intNum = rand()%intRange;
    intNum = intNum + intLowest;

    return intNum;
}

void GetOpt3(vector<int> vecNums)
{
    vector<int> vecMode = GetMode(vecNums);
    cout << "The mode for the numbers are: " << endl;
    OutputVector(vecMode);
}

void Sort(vector<int>& vecNums)
{
    sort(vecNums.begin(), vecNums.end()); //This line means, sorts the sequence from begin to end
}

vector<int> GetMode(vector<int> vecNums)
{
    vector<int> vecMode;
    //Sort our list of vectors
    Sort(vecNums);
    cout << "Sorted List: " << endl;
    OutputVector(vecNums);
    //
    vector<int> vecUnique = MakeUnique(vecNums);
    cout  << "Unique vector: " << endl;
    OutputVector(vecUnique);

    vector <int> vecCount = MakeCount(vecUnique, vecNums);
    cout << "Count vector:" << endl;
    OutputVector(vecCount);

    int intHighest (GetHighest(vecCount)); //Gets the highest in the veccount
    cout << "The highest count was: " << intHighest << endl;
    int intIterator = 0;
    for (int n : vecCount)
    {
     if (n==intHighest)
     {
         vecMode.push_back(vecUnique[intIterator]);
     }
     intIterator++;
    }

    return vecMode;
}

vector<int> MakeUnique(vector<int> vecNums)
{
    vector<int> vecUnique;
    Sort(vecNums);
    int intPrev = vecNums[0];
    vecUnique.push_back(intPrev);

    for (int n : vecNums)
    {
        if (intPrev != n )
        {
            vecUnique.push_back(n);
            intPrev = n;
        }
    }
    return vecUnique;
}

int CountNum(vector<int> vecNums, int intNum)
{
    int intSum = 0;

    for (int n : vecNums)
    {
        if(intNum == n)
        {
            intSum++;
        }
    }

    return intSum;
}

vector<int> MakeCount(vector<int> vecUnique,vector<int> vecNums)
{
    vector<int> vecCount;

    for(int n : vecUnique)
    {
        int intCount = CountNum(vecNums, n);
        vecCount.push_back(intCount);
    }

    return vecCount;
}

int GetHighest(vector<int> vecNums)
{
    Sort(vecNums);

    return vecNums[vecNums.size()-1];

}
