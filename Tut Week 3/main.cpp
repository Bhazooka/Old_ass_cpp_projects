#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int intDam1 = 0;
    int intDam2 = 0;
    int intDam3 = 0;
    int intDam4 = 0;

    double dblDam1 = 0.0;
    double dblDam2 = 0.0;
    double dblDam3 = 0.0;

    double dblSumWeight = 0.0;
    double dblWeightAvg = 0.0;
    int intStatus = 0;

    const int LOW = 1;
    const int MEDIUM = 2;
    const int HIGH = 3;

    const double ERR_MARGIN = 0.00001;

    const int SUCCESS = 0;
    const int ERR_CONV = -1;
    const int ERR_RANGE = -2;
    const int ERR_INPUT = -3;
    const int ERR_LOGIC = -4;

    //Dam 1
    /*
    1)Get input
    2)Validate input
    */

    cout << "Please enter 1st Dam level (0-100):";
    cin >> intDam1;
    if (cin.fail())
    {
        cerr << "Couldn't convert string into integer";
        //cerr is the error stream,
        exit (ERR_CONV);
    }
    if(intDam1 < 0 || intDam1 > 100) //this is an or operator, here we cant use && operator because a value cant be bigger than 100 and less than 0 at the same time. Remeber for AND, they both have to be true.
    {
        cerr << ("Please enter a value between 0 and 100");
        exit(ERR_RANGE);
    }

    //Dam 2
    /*
    1)Get input
    2)Validate input
    */
    cout << "Please enter 2nd Dam level (0-100):";
    cin >> intDam2;
    if (cin.fail())
    {
        cerr << "Couldn't convert string into integer";
        //cerr is the error stream,
        exit (ERR_CONV);
    }
    if(intDam2 < 0 || intDam2 > 100) //this is an or operator, here we cant use && operator because a value cant be bigger than 100 and less than 0 at the same time. Remeber for AND, they both have to be true.
    {
        cerr << ("Please enter a value between 0 and 100");
        exit(ERR_RANGE);
    }


    //Dam 3
    /*
    1)Get input
    2)Validate input
    */
    cout << "Please enter 3rd Dam level (0-100):";
    cin >> intDam3;
    if (cin.fail())
    {
        cerr << "Couldn't convert string into integer";
        //cerr is the error stream,
        exit (ERR_CONV);
    }
    if(intDam3 < 0 || intDam3 > 100) //this is an or operator, here we cant use && operator because a value cant be bigger than 100 and less than 0 at the same time. Remeber for AND, they both have to be true.
    {
        cerr << ("Please enter a value between 0 and 100");
        exit(ERR_RANGE);
    }



    //Get the wieghts for dam 1
    cout << "Please provide the weight for dam 1 (0.0 - 1.0)";
    cin >> dblDam1;
    //validate
    if (cin.fail())
    {
        cerr << "Could not convert string to double";
        exit (ERR_CONV);
    }
    if (dblDam1 < 0 || dblDam1 > 1)
    {
     cerr << "Please enter a value between 0 and 1";
     exit (ERR_RANGE);
    }

    //Get the wieghts for dam 2
    cout << "Please provide the weight for dam 2 (0.0 - 1.0)";
    cin >> dblDam2;
    //validate
    if (cin.fail())
    {
        cerr << "Could not convert string to double";
        exit (ERR_CONV);
    }
    if (dblDam2 < 0 || dblDam2 > 1)
    {
     cerr << "Please enter a value between 0 and 1";
     exit (ERR_RANGE);
    }

    //Get the wieghts for dam 3
    cout << "Please provide the weight for dam 3 (0.0 - 1.0)";
    cin >> dblDam3;
    //validate
    if (cin.fail())
    {
        cerr << "Could not convert string to double";
        exit (ERR_CONV);
    }
    if (dblDam3 < 0 || dblDam3 > 1)
    {
     cerr << "Please enter a value between 0 and 1";
     exit (ERR_RANGE);
    }


    dblSumWeight = dblDam1 + dblDam2 + dblDam3;
    // (1/3) + (1/3) + (1/3)
    // 0.333 + 0.333 + 0.333 = 0.999
    // Because some numbers cant exxactly equal to the values we want,
    // We have to create a margin of error (const double ERR_MARGIN)
    double dblRange1 = 1 - ERR_MARGIN;
    double dblRange2 = 1 + ERR_MARGIN;

    if (dblSumWeight < dblRange1 || dblSumWeight > dblRange2)
    {
        cerr << "Sum of the weight is not 1 ";
        //(!= means not equal to 1);
        exit(ERR_INPUT);

    }

    //Calculate the weighted average
    dblWeightAvg = (dblDam1 * intDam1) + (dblDam2 * intDam2) + (dblDam3 * intDam3);

    cout << "The weighted average is: " << dblWeightAvg << endl;

    //Change the status indicator
    if (dblWeightAvg>=0 && dblWeightAvg<60)
    {
        intStatus = LOW;
    }
    else if(dblWeightAvg >= 60 && dblWeightAvg < 80)
    {
        intStatus = MEDIUM;
    }
    else if (dblWeightAvg >= 80 && dblWeightAvg <= 100)
    {
        intStatus = HIGH;
    }
    else
    {
        cerr << "The weighted avg was either less than zero or greater than 100";
        exit (ERR_LOGIC);
    }

    switch(intStatus)
    {
        case LOW:
        {
            cout << "The water supply is currently low" << endl;
            break;
        }
        case MEDIUM:
        {
            cout << "The water supply is currently medium" << endl;
            break;
        }
        case HIGH:
        {
            cout << "The water supply is currently high" << endl;
            break;
        }
        default:
            {
                cout << "The status indicator probably didnt update." << endl;
            }

    }


    cout << (intStatus == LOW ? "Rather shower":"Have long baths");
    // == : is evaluating (meaning it checks if the values are equal)
    // =  : makes the left hand operand equal to theright hand operand
    return SUCCESS;
}
