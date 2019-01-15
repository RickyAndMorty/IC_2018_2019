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

void setDistanceBetweenUserAndStarCoupler(vector<double> DistanceBetweenUserAndStarCoupler)
{
    DistanceBetweenUserAndStarCoupler[0] = 48.8779;
    DistanceBetweenUserAndStarCoupler[1] = 26.9518;
    DistanceBetweenUserAndStarCoupler[2] = 40.0057;
    DistanceBetweenUserAndStarCoupler[3] = 46.3947;
    DistanceBetweenUserAndStarCoupler[4] = 18.7903;
    DistanceBetweenUserAndStarCoupler[5] = 22.8634;
    DistanceBetweenUserAndStarCoupler[6] = 37.3182;
    DistanceBetweenUserAndStarCoupler[7] = 5.2198;
    DistanceBetweenUserAndStarCoupler[8] = 32.6824;
    DistanceBetweenUserAndStarCoupler[9] = 48.5307;
    DistanceBetweenUserAndStarCoupler[10] = 10.2101;
    DistanceBetweenUserAndStarCoupler[11] = 40.0123;
    DistanceBetweenUserAndStarCoupler[12] = 14.8661;
    DistanceBetweenUserAndStarCoupler[13] = 26.3720;
    DistanceBetweenUserAndStarCoupler[14] = 46.7481;
    DistanceBetweenUserAndStarCoupler[15] = 29.7142;
    DistanceBetweenUserAndStarCoupler[16] = 28.8779;
    DistanceBetweenUserAndStarCoupler[17] = 36.9518;
    DistanceBetweenUserAndStarCoupler[18] = 30.0057;
    DistanceBetweenUserAndStarCoupler[19] = 16.3947;
    DistanceBetweenUserAndStarCoupler[20] = 8.7903;
    DistanceBetweenUserAndStarCoupler[21] = 32.8634;
    DistanceBetweenUserAndStarCoupler[22] = 27.3182;
    DistanceBetweenUserAndStarCoupler[23] = 4.2198;
    DistanceBetweenUserAndStarCoupler[24] = 12.6824;
    DistanceBetweenUserAndStarCoupler[25] = 28.5307;
    DistanceBetweenUserAndStarCoupler[26] = 40.2101;
    DistanceBetweenUserAndStarCoupler[27] = 30.0123;
    DistanceBetweenUserAndStarCoupler[28] = 34.8661;
    DistanceBetweenUserAndStarCoupler[29] = 26.3720;
    DistanceBetweenUserAndStarCoupler[30] = 26.7481;
    DistanceBetweenUserAndStarCoupler[31] = 19.7142;
    DistanceBetweenUserAndStarCoupler[32] = 27.3182;
    DistanceBetweenUserAndStarCoupler[33] = 5.2198;
    DistanceBetweenUserAndStarCoupler[34] = 6.6824;
    DistanceBetweenUserAndStarCoupler[35] = 7.5307;
    DistanceBetweenUserAndStarCoupler[36] = 20.2101;
    DistanceBetweenUserAndStarCoupler[37] = 8.0123;
    DistanceBetweenUserAndStarCoupler[38] = 9.8661;
    DistanceBetweenUserAndStarCoupler[39] = 12.3720;
    DistanceBetweenUserAndStarCoupler[40] = 11.7481;
    DistanceBetweenUserAndStarCoupler[41] = 13.7142;
    DistanceBetweenUserAndStarCoupler[42] = 7.3182;
    DistanceBetweenUserAndStarCoupler[43] = 13.2198;
    DistanceBetweenUserAndStarCoupler[44] = 12.6824;
    DistanceBetweenUserAndStarCoupler[45] = 38.5307;
    DistanceBetweenUserAndStarCoupler[46] = 48.2101;
    DistanceBetweenUserAndStarCoupler[47] = 36.0123;
    DistanceBetweenUserAndStarCoupler[48] = 4.8661;
    DistanceBetweenUserAndStarCoupler[49] = 6.3720;
    DistanceBetweenUserAndStarCoupler[50] = 27.7481;
    DistanceBetweenUserAndStarCoupler[51] = 15.7142;
    DistanceBetweenUserAndStarCoupler[52] = 24.3182;
    DistanceBetweenUserAndStarCoupler[53] = 41.2198;
    DistanceBetweenUserAndStarCoupler[54] = 14.6824;
    DistanceBetweenUserAndStarCoupler[55] = 8.5307;
    DistanceBetweenUserAndStarCoupler[56] = 10.2101;
    DistanceBetweenUserAndStarCoupler[57] = 20.0123;
    DistanceBetweenUserAndStarCoupler[58] = 30.8661;
    DistanceBetweenUserAndStarCoupler[59] = 6.3720;
    DistanceBetweenUserAndStarCoupler[60] = 46.7481;
    DistanceBetweenUserAndStarCoupler[61] = 29.7142;
    DistanceBetweenUserAndStarCoupler[62] = 36.7481;
    DistanceBetweenUserAndStarCoupler[63] = 39.7142;
}

int main()
{
    return 0;
}
