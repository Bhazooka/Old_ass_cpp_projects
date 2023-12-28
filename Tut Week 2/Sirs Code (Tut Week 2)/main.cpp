#include <iostream>

using namespace std;

int main()
{
    //Variables to store the km driven in the week
    const int intSun = 14;
    const int intMon = 45;
    const int intTue = 8;
    const int intWed = 2;
    const int intThu = 15;
    const int intFri = 26;
    const int intSat = 9;

    //Litres per 100 km
    const int intFuelKm = 8;
    const int intFuelRation = 100;

    //Rand per litre of fuel
    const double dblCostPerL = 20.25;

    //Calculate the total km driven
    int intTotalKm = intSun +
                     intMon +
                     intTue +
                     intWed +
                     intThu +
                     intFri +
                     intSat;
    cout << "Total kilometers driven in the past week" << endl;
    cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSat\t" << endl;
    cout << intSun << '\t' <<
            intMon << '\t' <<
            intTue << '\t' <<
            intWed << '\t' <<
            intThu << '\t' <<
            intFri << '\t' <<
            intSat << '\t' << endl << endl;

    cout << "The total km driven was: " << intTotalKm << "km" << endl;

    //Calculate the Total fuel used (How much litres)
    double dblFuelUsed = 0.0;
    dblFuelUsed = static_cast<double>(intTotalKm) / intFuelRation * intFuelKm;
    cout << "The total fuel used in the week is:" << dblFuelUsed << "l" << endl;

    //Calculate the total cost given R20.25 per litre.
    double dblTotalCost = dblFuelUsed * dblCostPerL;
    cout << "The total cost for the past week is:R" << dblTotalCost << endl;

    return 0;
}
