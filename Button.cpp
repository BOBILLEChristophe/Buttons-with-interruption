

#include "Button.h"

Button::Button() :
  id(0),
  pin(255),
  compt(0),
  pressed(false),
  duration(0),
  currentState(false),
  lastDebounceTime(0),
  debonceTempo(10)
{}

void Button::isr0 () {
  inst0->handleInterrupt();
} 
void Button::isr1 () {
  inst1->handleInterrupt();
}
void Button::isr2 () {
  inst2->handleInterrupt();
}

Button *Button::inst0;
Button *Button::inst1;
Button *Button::inst2;

void Button::setup(const uint8_t id, const uint8_t pin) {
  this->id = id;
  this->pin = pin;
  pinMode(this->pin, INPUT_PULLUP);

  switch (this->id)
    {
    case 0: 
      attachInterrupt (this->pin, isr0, CHANGE); 
      inst0 = this;
      break;
    case 1: 
      attachInterrupt (this->pin, isr1, CHANGE); 
      inst1 = this;
    break;
    case 2: 
      attachInterrupt (this->pin, isr2, CHANGE); 
      inst2 = this;
    break;
    }  
}

bool Button::loop() {
  bool err = 1;
  if (this->pressed) {
    this->pressed = false;
    err = 0;
  }
  return err;
}

void IRAM_ATTR Button::handleInterrupt() {
  if (millis() > (this->lastDebounceTime + this->debonceTempo)) {
    this->duration = (millis() - this->lastDebounceTime) > BTN_PUSH_TIME ? LONG : COURT;
    this->lastDebounceTime = millis();
    if (this->currentState) {
      this->compt++;
      this->pressed = true;
    }
    this->currentState = ! this->currentState;
  }
}
