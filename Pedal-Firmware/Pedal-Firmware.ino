#include "Arduino.h"
#include "Keyboard.h"

struct Button {
  int pinNumber;
  bool isActivated;
  int keys[3];
};

Button buttons[3] = {{2, false, {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT}},
                     {3, false, {KEY_LEFT_CTRL}},
                     {4, false, {KEY_LEFT_SHIFT}}};

void setup() {
  for (Button &button : buttons) {
    pinMode(button.pinNumber, INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop() {
  for (Button &button : buttons) {
    if (!button.isActivated && digitalRead(button.pinNumber) == LOW) {
      for (int k : button.keys) {
        Keyboard.press(k);
      }
      button.isActivated = true;
      delay(10);
    }
    if (button.isActivated && digitalRead(button.pinNumber) == HIGH) {
      for (int k : button.keys) {
        Keyboard.release(k);
      }
      button.isActivated = false;
      delay(10);
    }
  }
}
