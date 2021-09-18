#include <iostream>
using namespace std;

#define prescaler             8
#define ticks_overflow        65536
#define ticks_periode         ((float) prescaler / 16)
#define ticks_for_us(time_us) ((float) ticks_overflow - \
                               (time_us / ticks_periode))

int main(int argc, char const* argv[]) {
    float time_us = 10E3;
    cout << "Time us:                 " << time_us << endl;
    cout << "Periodo de ticks:        " << ticks_periode << endl;
    cout << "Ticks para tiempo X[us]: " << ticks_for_us(time_us) << endl; // 10 ms

    return 0;
}