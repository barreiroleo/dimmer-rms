#ifndef Interrupt_h
#define Interrupt_h
#include <Arduino.h>
#include "DebugSerial.h"

#define interruptPin 2

void ISR_INT();
void init_INT();


void init_INT() {
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_INT, RISING);
}


void ISR_INT() {
    // println_debug("Interrupt. Reset timer!: " + String(TCNT1));
    uint16_t previous_ticks = TCNT1;
    TCNT1 = 0;
    semi_periode = previous_ticks * peri_ticks;
    flag_print = 1;
}

#endif