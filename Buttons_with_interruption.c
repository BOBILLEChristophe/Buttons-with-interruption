#define NB_BTN 3
#define BTN_PUSH_TIME 500

enum {COURT, LONG};

struct Button {
  uint8_t    pin;
  uint8_t    compt;
  bool       pressed;
  bool       duration;
  bool       currentState;
  uint64_t   lastDebounceTime;
  uint8_t    debonceTempo;
};

Button button[NB_BTN];

void IRAM_ATTR isr0() {
  isrProcess(0);
}

void IRAM_ATTR isr1() {
  isrProcess(1);
}

void IRAM_ATTR isr2() {
  isrProcess(2);
}

void isrProcess(byte x) {
  if (millis() > (button[x].lastDebounceTime + button[x].debonceTempo)) {
    button[x].duration = (millis() - button[x].lastDebounceTime) > BTN_PUSH_TIME ? LONG : COURT;
    button[x].lastDebounceTime = millis();
    if (button[x].currentState) {
      button[x].compt++;
      button[x].pressed = true;
      Serial.println(button[x].duration);
    }
    button[x].currentState = ! button[x].currentState;
  }
}

void (*ptrFunct[NB_BTN])() = {isr0, isr1, isr2};

void setup() {
  
  Serial.begin(115200);

  button[0] = {18, 0, false, 0, 0, 0, 10};
  button[1] = {19, 0, false, 0, 0, 0, 10};
  button[2] = {21, 0, false, 0, 0, 0, 10};
  
  for (byte i = 0; i < NB_BTN; i++) {
    pinMode(button[i].pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(button[i].pin), ptrFunct[i], CHANGE);
  }
}

void loop() {
  for (byte i = 0; i < NB_BTN; i++) {
    if (button[i].pressed) {
      Serial.printf("Le boutton %d a été appuyé %d fois\n", i, button[i].compt);
      button[i].pressed = false;
    }
  }
}

