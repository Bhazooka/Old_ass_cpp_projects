#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    bool blnRunFlag = true;
    char chOption = '\0';

    do
    {
        //create menue
        system ("cls"); //clears the menue everytime an option has been selected. Without this, your options will keep reapearing everytime you choose an option. It will reapear below the previous option prompt.
        cout << "Option A: Run a number sequence" << endl
             << "Option B: Determine if a number is prime" << endl
             << "Option C: Get non-vowel characters" <<endl
             << "Option D: Quit" << endl;
             cin >> chOption;

             switch(chOption)
             {
                 case 'a':
                 case 'A':
                 {
                     int intTerms = 0;
                     cout << "how many terms do you want to output?: ";
                     cin >> intTerms;

                     while(cin.fail())
                     {
                         cin.clear();
                         string strRubish;
                         cin >> strRubish;

                         cerr << "could not convert to integer or value was not a positive number"<< endl;
                         cout << "how many terms do you want to output?: ";
                         cin >> intTerms;
                     }

                     if (intTerms <= 0)
                     {
                         cerr << "Please use a positive number for the number of terms" << endl;
                         break;
                     }

                     for(int n = 1; n <= intTerms; n++)
                     {
                         cout << (n * (n-1)) << " ";
                     }
                     cout << endl;

                     break;

                 }
                 case 'b':
                 case 'B':
                 {
                     int intNum = 0;
                     bool blnIsPrime = true;
                     cout << "Please type in any positive number: ";
                     cin >> intNum;

                     //validation
                     while (cin.fail())
                     {
                         cin.clear();
                         string strRubish;
                         cin >> strRubish;

                         cerr << "could not convert to integer or value was not a positive number"<< endl;
                         cout << "how many terms do you want to output?: ";
                         cin >> intNum;
                     }

                     for(int n=2; n < intNum; n++)
                     {
                         if (intNum % n == 0)
                         {
                            blnIsPrime = false;
                         }
                     }
                     cout << intNum<< (blnIsPrime? " is a prime number" : " is NOT a prime number") << endl;
                     break;

                 }
                 case 'c':
                 case 'C':
                 {
                     cout << "Please type in a sentence: " << endl;
                     string strSentence;
                     cin.ignore(100, '\n');
                     getline(cin,strSentence); //

                     for (char c: strSentence)
                     {
                         switch(c)
                         {
                             case 'a':
                             case 'A':
                             case 'e':
                             case 'E':
                             case 'i':
                             case 'I':
                             case 'o':
                             case 'O':
                             case 'u':
                             case 'U':
                             {
                                 break;
                             }
                             default:
                             {
                                 cout << c;
                             }

                         }

                     }
                     cout << endl;
                     break;
                 }

                 case 'd':
                 case 'D':
                 {
                    blnRunFlag = false;
                     break;

                 }
                 default:
                 {
                     cerr << "Please select a valid option (A-D)" << endl;
                 }
             }

             //Pause function
             cout << "Press Enter to continue" << endl;
             cin.ignore(100, '\n'); //When wanting to enter new options, the c++ keeps a record of what you had entered before.
             // The ignore code tells c++ to ignore the previous 100 characters until the first new line (or enter) character, so you can enter new values (or in this case options)
            //100 characters is just a safe zone estimation for the amount of characters is needed. If there was more than 100 then you would raise the number.
        cin.get();

    }while(blnRunFlag == true); //Keep executing the while loop while blnRunFlag is true. you can either write it as (blnRunFlag == true) or (blnRunFlag), but as long as the code evalutes that its true it will keep running


    return 0;
}
