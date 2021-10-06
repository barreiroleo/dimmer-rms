#ifndef Timer1_h
#define Timer1_h

#include <Arduino.h>
#include "DebugSerial.h"

void init_TMR1();
void set_timer_1(uint16_t);


void init_TMR1() {
    noInterrupts();
    // Timer Counter Control Register A:
    // Normal port operation, OC1A/OC1B disconnected.
    // Waveform Generation Mode: Normal. Overflow en 0xFFFF.
    TCCR1A = 0;

    // Timer Counter Control Register B: Prescaler 8
    //          CS12 | CS11 | CS10  ||           CS12 | CS11 | CS10
    // Stop      0   |  0   |  0    ||  clk/64    0   |  1   |  1  
    // clk/1     0   |  0   |  1    ||  clk/256   1   |  0   |  0  
    // clk/8 ->  0   |  1   |  0    ||  clk/1024  1   |  0   |  1  
    TCCR1B &= ~((1 << CS12) | (1 << CS10));
    TCCR1B |= (1 << CS11);

    // Interrupt Mask Register.
    TIMSK1 |= (1 << OCIE1A) | (1 << TOIE1);

    // Timer Counter. Output Compare Register A y B.
    TCNT1 = 0; OCR1A = 0; OCR1B = 0;

    // Timer Counter Int Flag Register. Clear register.
    // TIFR1 = 0;
    interrupts();
}


ISR(TIMER1_COMPA_vect) {
    /**
     * @brief
     * Interrupcion por comparación Timer vs OCR0A.
     * Disparar triac. Timer sigue corriendo hasta detectar nuevo cruce por cero
     * o hasta desbordar.
    **/

    // println_debug("TMR1 Time match");
    digitalWrite(13, HIGH);
    delayMicroseconds(10);
    digitalWrite(13, LOW);
}


ISR(TIMER1_OVF_vect) {
    /**
     * @brief
     * Interrupcion cuando desborda el timer.
     * Si hay desborde es porque no hay detecciones nuevas de cruce por cero.
    **/

    // println_debug("TMR1 Overflow");
    TCNT1 = 0;
}


#define frec_cpu_MHz 16
#define prescaler 8
#define peri_ticks ((float) 1 / ((frec_cpu_MHz) / (prescaler)))

void set_timer_1(uint16_t time_us) {
    uint16_t time_in_ticks  = (uint16_t)time_us / peri_ticks;
    Serial.print("; ticks: "); Serial.println(time_in_ticks);
    // println_debug("Ticks for time: " + String(time_in_ticks));

    /**
     * Si OCR1A ~= 20 hay salida de onda completa.
     * Se dan 30 ticks para mayor estabilidad. No hay diferencia apreciable
     * en osciloscopio. //TODO Probar en producto final
    **/
    if (time_us == 0) {
        OCR1A = 10;
    }
    else {
        OCR1A = time_in_ticks;
    }
}
#endif