#ifndef Timer1_h
#define Timer1_h

#include <Arduino.h>
#define prescaler             8
#define ticks_overflow        65536
#define ticks_periode         ((float) prescaler / 16)
#define ticks_for_us(time_us) ((float) ticks_overflow - \
                               (time_us / ticks_periode))


void init_TMR1() {
    /**
     * @brief
     * Configuración de registros del Timer 1.
     * Register Description en capitulo 16.11. Interrupt vectors en tabla 12-6
     */
    noInterrupts();

    // Timer Counter Control Register A.
    // Compare output mode for Channel A and Channel B.
    TCCR1A = 0b00000000;

    // Timer Counter Control Register B.
    // Input capture Noise Canceler. Demora 4 ciclos la lectura.
    // Prescaler clk / 8.
    // Stop :    000;   clk/1:    001
    // clk/8:    010;   clk/64:   011
    // clk/256:  100;   clk/1024: 101
    TCCR1B = 0b10000010;

    // Timer Counter Control Register C.
    TCCR1C = 0b00000000;

    // Timer Counter.
    TCNT1 = 0;

    // Output Compare Register 1 A
    OCR1A = 0;
    // Output Compare Register 1 B
    OCR1B = 0;

    // Input Capture Register 1
    ICR1 = 0;

    // Interrupt Mask Register
    // Output Compare A Match Interrupt Enable
    // Overflow Interrupt Enable
    // TIMSK1 = 1 << OCIE1A | 1 << TOIE1;
    TIMSK1 = 0b00000011;

    interrupts();
}


ISR(TIMER1_COMPA_vect) {
    /**
     * @brief
     * Interrupcion cuando se alcanza la carga de comparación OCR0A.
     * Reiniciar timer. Disparar triac.
     */
    Serial.println("Time match");
    TCNT1 = 0;
}


ISR(TIMER1_OVF_vect) {
    /**
     * @brief
     * Interrupcion cuando desborda el timer.
     * Si el valor objetivo de RMS es distinto a cero dar mensaje de error.
     */
    Serial.println("Hey, overflow");
    TCNT1 = 0;
}


void set_timer_1(uint16_t time_us) {
    OCR1A = (int)ticks_for_us(time_us);
}

#endif