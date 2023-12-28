#include <iostream>
//Use the cstldib library to ensure the system - function can work properly
#include <cstdlib>

using namespace std;

int main()
{
    char chInput = '\0';            //Variable to store the menu option in
    bool blnContinue = true;        //Flag that controls the menu loop

    do                              //Start of the do-while loop
    {
        //Clear the screen by call the console cls command.
        system("clear");    //If we are using Windows, then replace this with system("cls");
        cout << "A) Sequence of numbers" << endl;
        cout << "B) Prime number testing" << endl;
        cout << "C) Non-vowel filter" << endl;
        cout << "D) Quit the program" << endl;
        cout << "Please select a menu option:";
        //Get input from the standard input stream
        cin >> chInput;

        //Evaluate the input and run the specific section code
        switch(chInput)
        {
        case 'a':
        case 'A':
        {
            int intNum = 0;                     //Localised variable inside the {} braces to store the number
            cout << "Please type in a number:";
            cin >> intNum;
            //Repeate until the user types in a proper number
            while(cin.fail())
            {
                cin.clear();                    //Clear the fail flag from cin
                string strJunk;                 //Define a variable to store all the characters from the std input stream
                cin >> strJunk;                 //Clear the std input stream
                cerr << "Invalid value." << endl;
                cout << "Please try again:";
                cin >> intNum;
            }

            //Loop for all the numbers starting at 1, until just before the input number
            for(int n=1;n<=intNum;n++)
            {
                cout <<  n * (n-1) << " ";
            }
        }
            //Sequence numbers
            break;
        case 'b':
        case 'B':
            //Prime number testing
        {
            int intNum = 0;                         //Localised integer to store the number in from the user
            bool blnIsPrime = true;                 //Use a flag to assume the number is a prime number
            cout << "Please type in a number:";
            cin >> intNum;
            while(cin.fail() || intNum<=1)          //If the number conversion failed or if the number was less than or equal to 1 then
            {
                cin.clear();                        //Clear the fail flag
                cin.ignore(500,'\n');               //Clear the characters from the input stream up to the first new line character
                cerr << "Invalid value." << endl;
                cout << "Please try again:";
                cin >> intNum;
            }

            //Start counting at half the number, decrement the number at each iteration while n>1
            for(int n=intNum/2;n>1;n--)
            {
                if(intNum%n == 0)           //See if the n divided into intNum's remainder is equal to zero (ie. it successfully divided)
                {
                    blnIsPrime = false;     //Then the number is not a prime
                }
            }

            //Test the value of blnPrime, if it is true, make strOutput = "The number is prime" else make it "The number is NOT prime"
            string strOutput = (blnIsPrime?"The number is prime":"The number is NOT a prime");
            cout << strOutput << endl;
        }
            break;

        case 'c':
        case 'C':
            //Non-vowel filter
        {
            string strWord;
            cout << "Please type in a string of characters" << endl;
            //cin >> strWord;
            cin.ignore(100,'\n');           //Clear the input buffer for any possible
            getline(cin,strWord);           //Read in all the characters up to the end-line character

            //For each character in strWord, add the character to chChar and run the code
            for(char chChar : strWord)
            {
                //Look at the value of chChar.  If it is vowel, then do nothing
                switch(chChar)
                {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                    //Dont do anything if it is a vowel
                    break;
                default:
                    //Output if it is non-vowel
                    cout << chChar;
                }
            }
        }

            break;
        case 'd':
        case 'D':
            //Quit the program
            blnContinue = false;
            break;
        default:
            //For everything else
            cerr << "Invalid option please try again" << endl;
        }
        //Pause function
        cout << "Press Enter to continue" << endl;
        cin.ignore(100,'\n');
        cin.get();
        
    }while(blnContinue);

    return 0;
}
