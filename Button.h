#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

enum {COURT, LONG};

class Button {
  private:

    static void isr0 ();
    static void isr1 ();
    static void isr2 ();

    static Button * inst0;
    static Button * inst1;
    static Button * inst2;
    void handleInterrupt ();

    uint8_t          pin;
    bool             pressed;
    bool             currentState;
    uint64_t         lastDebounceTime;
    const uint8_t    debonceTempo;

  public:
  
    Button(); // Constructeur
    
    uint8_t          id;
    bool             duration;
    volatile uint8_t compt;

    void setup(const uint8_t, const uint8_t);
    bool loop();
    void IRAM_ATTR isr();
    void isrProcess(byte);
};


#endif /* defined(BUTTON_H) */
