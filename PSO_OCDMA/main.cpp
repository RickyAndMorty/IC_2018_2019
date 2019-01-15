#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


void  calculateSignalToNoiseRatio(vector<double> signalToNoiseRatio, double** signalToNoiseInterferenceRatio, int lines, int column)
{
    for(int index = 0; index < signalToNoiseRatio.size(); index ++)
    {
        signalToNoiseRatio[index] = 10.00F * (logf(signalToNoiseInterferenceRatio[index][column-1] * ((256*256) /0.0100 )) / logf(10.00F));
    }
}


int main()
{
    return 0;
}
