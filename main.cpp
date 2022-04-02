
#include "Button.h"

#define NB_BTN 3

/*---- Instances Boutons ----*/
Button button[NB_BTN];

void setup() {

  button[0].setup(0, BTN_0_PIN);
  button[1].setup(1, BTN_1_PIN);
  button[2].setup(2, BTN_2_PIN);

 
void loop() {

  // Lecture etat boutons
  for (byte i = 0 ; i < NB_BTN; i++) {
    bool err = button[i].loop();
    if (err == 0) {
      Serial.printf("Le boutton %d a été appuyé %d fois\n", button[i].id, button[i].compt);
    }
  }
}
