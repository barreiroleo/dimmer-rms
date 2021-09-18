#ifndef DebugSerial_h
#define DebugSerial_h

#ifdef DebugSerial
  #define print_debug(...) Serial.print(__VA_ARGS__)
  #define println_debug(...) Serial.println(__VA_ARGS__)
#else
  #define print_debug(...)
  #define println_debug(...)
#endif

#endif