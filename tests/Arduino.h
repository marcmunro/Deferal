/* Stub header for Arduino.h
 * This allows simple unit testing to be performed.
 */

#ifndef ARDUINO_HDR
#define ARDUINO_HDR

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Arduino-specifc types
 */
typedef unsigned char		byte;
typedef uint16_t		word;

/* delay() and associates
 */
unsigned long millis(void);
unsigned long micros(void);
extern void delay(unsigned long millis);

/* Digital IO
 */
#define INPUT  0
#define OUTPUT 1
extern void pinMode(int pin, int value);
extern int digitalRead(int pin);
extern void digitalWrite(int pin, int value);

/* Interupt handling 
 */
#define RISING 3
typedef void isr_fn_t();
extern int digitalPinToInterrupt(int pinNo);
extern void attachInterrupt(int pin, isr_fn_t *fn, int type);

/* Serial
 */


class HardwareSerial {
public:
    static void begin(unsigned long baud_rate);
    static size_t println(const char *str);
};

extern HardwareSerial Serial;

#endif
