#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    //Variables used in the program
    int intDam1 = 0;
    int intDam2 = 0;
    int intDam3 = 0;
    
    double dblDam1 = 0.0;
    double dblDam2 = 0.0;
    double dblDam3 = 0.0;
    
    double dblSumWeight = 0.0;
    double dblWeightedAvg = 0.0;
    int intStatus = 0;
    
    //const variables
    const int LOW = 1;
    const int MEDIUM = 2;
    const int HIGH = 3;
    
    const double MARGIN_ERROR = 0.00001;
    
    const int SUCCESS = 0;
    const int ERR_CONV = -1;
    const int ERR_RANGE = -2;
    const int ERR_INPUT = -3;
    const int ERR_LOGIC = -4;
    
    /*
    1) Get input
    2) Validate input
    */
    //Dam1
    //Get input
    cout << "Please enter the dam level (0-100) for dam 1:";
    cin >> intDam1;
    //Validate input
    if(cin.fail())
    {
        cerr << "Could not convert string to integer";
        exit(ERR_CONV);
    }
    if(intDam1 < 0 || intDam1 > 100)
    {
        cerr << "Please enter values between 0 and 100";
        exit(ERR_RANGE);
    }
    
    //Dam2
    //Get input
    cout << "Please enter the dam level (0-100) for dam 2:";
    cin >> intDam2;
    //Validate input
    if(cin.fail())
    {
        cerr << "Could not convert string to integer";
        exit(ERR_CONV);
    }
    if(intDam2 < 0 || intDam2 > 100)
    {
        cerr << "Please enter values between 0 and 100";
        exit(ERR_RANGE);
    }
    
    //Dam3
    //Get input
    cout << "Please enter the dam level (0-100) for dam 3:";
    cin >> intDam3;
    //Validate input
    if(cin.fail())
    {
        cerr << "Could not convert string to integer";
        exit(ERR_CONV);
    }
    if(intDam3 < 0 || intDam3 > 100)
    {
        cerr << "Please enter values between 0 and 100";
        exit(ERR_RANGE);
    }
    
    
    //Get the weight for dam 1
    cout << "Please provide the weight for dam 1 (0.0 - 1.0)";
    cin >> dblDam1;
    //Validate input
    if(cin.fail())
    {
        cerr << "Could not convert string to double";
        exit(ERR_CONV);
    }
    if(dblDam1 < 0 || dblDam1 > 1)
    {
        cerr << "Please enter a value between 0 and 1";
        exit(ERR_RANGE);
    }
    
    //Get the weight for dam 2
    cout << "Please provide the weight for dam 2 (0.0 - 1.0)";
    cin >> dblDam2;
    //Validate input
    if(cin.fail())
    {
        cerr << "Could not convert string to double";
        exit(ERR_CONV);
    }
    if(dblDam2 < 0 || dblDam2 > 1)
    {
        cerr << "Please enter a value between 0 and 1";
        exit(ERR_RANGE);
    }
    
    //Get the weight for dam 3
    cout << "Please provide the weight for dam 3 (0.0 - 1.0)";
    cin >> dblDam3;
    //Validate input
    if(cin.fail())
    {
        cerr << "Could not convert string to double";
        exit(ERR_CONV);
    }
    if(dblDam3 < 0 || dblDam3 > 1)
    {
        cerr << "Please enter a value between 0 and 1";
        exit(ERR_RANGE);
    }
    
    dblSumWeight = dblDam1 + dblDam2 + dblDam3;
    // (1/3) + (1/3) + (1/3)
    // 0.333 + 0.333 + 0.333 = 0.999 (0.001)
    double dblRange1 = 1-MARGIN_ERROR;
    double dblRange2 = 1+MARGIN_ERROR;
    if(dblSumWeight < dblRange1 || dblSumWeight > dblRange2)
    {
        cerr << "Sum of the weight != 1";
        exit(ERR_INPUT);
    }
    
    //Calculate the weighted average
    dblWeightedAvg = (intDam1 * dblDam1) +
                     (intDam2 * dblDam2) +
                     (intDam3 * dblDam3);
                     
    cout << "The weighted avg is:" << dblWeightedAvg << endl;
    
    //Change the status indicator
    if(dblWeightedAvg >= 0 && dblWeightedAvg < 60)
    {
        intStatus = LOW;
    }
    else if(dblWeightedAvg >= 60 && dblWeightedAvg < 80)
    {
        intStatus = MEDIUM;
    }
    else if(dblWeightedAvg >= 80 && dblWeightedAvg <= 100)
    {
        intStatus = HIGH;
    }
    else
    {
        cerr << "The weighted avg was either less than zero or greater than 100";
        exit(ERR_LOGIC);
    }
    
    //Output a status message given the status level
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
            cerr << "The status indicator probably did not update." << endl;
        }
    }
    
    cout << (intStatus == LOW ?"Rather shower":"Have long baths") << endl;
    
    return SUCCESS;
}