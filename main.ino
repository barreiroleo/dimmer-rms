/**
 * @file main.ino
 * @author Leonardo A. Barreiro (github.com/barreiroleo)
 * @version 0.1
 * @date 2021-09-16
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
 */

// HACK: Desactiva optimizaciones de código para debug en proteus.
#pragma GCC optimize ("-O0")
#pragma GCC push_options
// #define DebugSerial

#include <Arduino.h>
#include "src/DebugSerial.h"

#include "src/Timer1.h"
#include "src/Interrupt.h"


void setup() {
    Serial.begin(9600);
    init_TMR1();
    init_INT();

    pinMode(13, OUTPUT);
    set_timer_1(1E3);
}


void loop() {
}


#pragma GCC pop_options