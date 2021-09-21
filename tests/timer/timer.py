# @file timer.cpp
# @author Leonardo A. Barreiro (github.com/barreiroleo)
# @version 0.1
# @date 2021-09-18
# @copyright Copyright (c) 2021
# @tags: /BUG   Hay comportamientos inesperados.
#        /HACK  Solución rápida, debe reescribirse en un futuro.
#        /FIXME Necesita reparación, no funciona.
#        /TODO  Item por implementar o tarea por hacer.
#        /XXX   Cualquier anotación que no entre en las categorías anteriores.
# @brief 

import argparse


class Timer:
    def __init__(self, time_us: float, prescaler: int, resolution: int, frec_cpu_MHz: int = 16) -> None:
        """
        Args:
            time_us (float): Tiempo en us a convertir en ticks
            prescaler (int): División de frecuencia a utilizar
            resolution (int): Resolución del timer.
            frec_cpu_MHz (int, optional): Frecuencia de CPU en MHz.
        """
        self.time_us = time_us
        self.prescaler = prescaler
        self.resolution = resolution
        self.frec_cpu_MHz = frec_cpu_MHz

    def statistics(self):
        self.frec_ticks = self.frec_cpu_MHz / self.prescaler
        self.peri_ticks = 1 / self.frec_ticks

        self.ticks_overflow = 2**self.resolution
        self.time_overflow  = self.peri_ticks * self.ticks_overflow

        self.time_in_ticks  = self.time_us / self.peri_ticks
        self.ticks_for_time = self.ticks_overflow - self.time_in_ticks

        print("Frecuencia de ticks  : {0:>8} [MHz]".format(self.frec_ticks))
        print("Período entre ticks  : {0:>8} [us]".format(self.peri_ticks))
        print("Ticks para overflow  : {0:>8} [raw]".format(self.ticks_overflow))
        print("Tiempo para overflow : {0:>8} [us]".format(self.time_overflow))
        print("Tiempo X en ticks    : {0:>8} [us]".format(self.time_in_ticks))
        print("Ticks desborde en X  : {0:>8} [raw]".format(self.ticks_for_time))


def main():
    time_us, frec_cpu_MHz, prescaler, resolution = parse_argv()
    timer = Timer(time_us, prescaler, resolution, frec_cpu_MHz)
    timer.statistics()


def parse_argv():
    """Parsea los argumentos de entrada.
    Se admite unidad ('us', 'ms' o 's'), prescaler, resolución y frecuencia.

    Returns:
        list: [tiempo_s: float, frec_MHz: int, prescaler: int, resolution: int]        
    """
    def convert_time(args):
        time = args.time * 1E0 if args.unit == "us" else None
        time = args.time * 1E3 if args.unit == "ms" else time
        time = args.time * 1E6 if args.unit == "s" else time
        return time
    
    help_string = "Calcula ticks necesarios para desbordar Timer 1 en Atmega328 en un tiempo dado"
    parser = argparse.ArgumentParser(description="{0}".format(help_string))
    parser.add_argument("time", type=float, help="Tiempo a calcular en ticks. Por defecto en [us]")
    parser.add_argument("-u", "--unit", choices=["us", "ms", "s"], default="us",
                        help="Define la unidad del tiempo. Por defecto en [us].")
    parser.add_argument("-p", "--prescaler",  type=int,
                        default=1,  help="Divisor de prescaler")
    parser.add_argument("-r", "--resolution", type=int,
                        default=16, help="Resolución del timer en [bits]")
    parser.add_argument("-f", "--frequency",  type=int,
                        default=16, help="Frecuencia de CPU en [MHz]")
    args = parser.parse_args()

    time = convert_time(args)
    print(args)
    return [time, args.frequency, args.prescaler, args.resolution]


if __name__ == "__main__":
    main()
