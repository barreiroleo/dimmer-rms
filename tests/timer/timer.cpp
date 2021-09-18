#include <iostream>
using namespace std;

#define PWR2(x) (1 << (x))
#define frec_cpu_MHz 16
#define prescaler 8
#define resolution 16
#define ticks_overflow PWR2(resolution)
#define peri_ticks ((float) 1 / ((frec_cpu_MHz) / (prescaler)))


int main(int argc, char const* argv[]) {
    float time_us = 10E3;
    // cout << "Time us:                 " << time_us << endl;
    // cout << "Periodo de ticks:        " << ticks_periode << endl;
    // cout << "Ticks para tiempo X[us]: " << ticks_for_us(time_us) << endl; // 10 ms

    uint16_t time_in_ticks  = (time_us / peri_ticks);
    uint16_t ticks_for_time = ticks_overflow - time_in_ticks;

    cout << ticks_for_time << endl;
    return 0;
}