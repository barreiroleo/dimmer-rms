/**
 * @file main.ino
 * @author Leonardo A. Barreiro (github.com/barreiroleo)
 * @version 0.1
 * @date 2021-09-16
 * @copyright Copyright (c) 2021
 * @brief
 * @tags: BUG:   En condiciones normales funciona. Puede dar comportamientos inesperados.
 *        HACK:  Solución rápida, debe reescribirse en un futuro.
 *        FIXME: Necesita reparación, no funciona.
 *        TODO:  Item por implementar o tarea por hacer.
 *        XXX:   Cualquier anotación que no entre en las categorías anteriores.
 */

// HACK: Desactiva optimizaciones de código para debug en proteus.
#pragma GCC optimize ("-O0")
#pragma GCC push_options

#include <Arduino.h>
#include "src/Globals.h"
#include "src/Interrupt.h"


void setup() {
    Serial.begin(9600);
    init_freq_meter();
}


void loop() {
}


#pragma GCC pop_options