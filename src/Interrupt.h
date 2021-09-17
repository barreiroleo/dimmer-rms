#ifndef Interrupt_h
#define Interrupt_h


#include <Arduino.h>

#define interruptPin 2
volatile float freq_now;


void ISR_INT();
void init_freq_meter();


void init_freq_meter() {
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_INT, RISING);
}


void ISR_INT() {
    /**
     * @brief
     * En cada flanco resetea la carga del TMR1 y se escribe la precarga
     * segun el tiempo objetivo. Además se restaura el flag de overflow.
     */
    TCNT1 = 0;
    Serial.println("Hey interrupt");
}

#endif