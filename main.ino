/**
 * @file main.ino
 * @author Leonardo A. Barreiro (github.com/barreiroleo)
 * @version 0.1
 * @date 2021-09-12
 * @copyright Copyright (c) 2021
 * @tags: BUG   Hay comportamientos inesperados.
 *        HACK  Solución rápida, debe reescribirse en un futuro.
 *        FIXME Necesita reparación, no funciona.
 *        TODO  Item por implementar o tarea por hacer.
 *        XXX   Cualquier anotación que no entre en las categorías anteriores.
 * @brief
 * En cada interrupción de cruce por cero reiniciar la carga de Timer1.
 * Si hay un nuevo setpoint calcular la carga del registro de comparación OCR1A.
 * El overflow del timer debe estar más lejos que el semiciclo de la onda.
 * El Timer debe estar en modo normal y no CTC (Clear Timer on Compare Match).
 * De esta manera, si el tiempo de comparación es una fracción del semiciclo,
 * se evitan los redisparos de triac. Además, si existe una interrupción por
 * desborde de Timer1, se sabrá que no está funcionando correctamente el bloque
 * de detección de cruce.
**/

// HACK: Desactiva optimizaciones de código para debug en proteus.
#pragma GCC optimize ("-O0")
#pragma GCC push_options

#include <Arduino.h>
#include "src/DebugSerial.h"
uint16_t semi_periode = 10E3;
bool flag_print = 0;

#include "src/Timer1.h"
#include "src/Interrupt.h"
#include "src/Dimmer.h"


void setup() {
    Serial.begin(9600);
    init_TMR1();
    init_INT();
    pinMode(13, OUTPUT);
}


#define LENGHT(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define max_index 255
#define min_index 0
void loop() {
    uint8_t rms_setpoint_index = 255;
    rms_time_calc(rms_setpoint_index);
    while (1) {
        if (digitalRead(3) && rms_setpoint_index < max_index) {
            rms_setpoint_index++;
            rms_time_calc(rms_setpoint_index);
        }
        if (digitalRead(4) && rms_setpoint_index > min_index) {
            rms_setpoint_index--;
            rms_time_calc(rms_setpoint_index);
        }
        if (flag_print) {
            Serial.print("Per: "), Serial.println(semi_periode);
            flag_print = 0;
        }
    }
}

#pragma GCC pop_options