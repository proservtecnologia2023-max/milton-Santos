#ifndef BUTTONS_H
#define BUTTONS_H

#include "config.h"

// ============================================
// BIBLIOTECA DE LEITURA DE BOTOEIRAS
// ============================================

class ButtonController {
private:
  int buttonPins[6];
  boolean buttonStates[6];
  boolean lastButtonStates[6];
  unsigned long lastDebounceTime[6];
  
public:
  ButtonController() {
    buttonPins[0] = BUTTON_1;
    buttonPins[1] = BUTTON_2;
    buttonPins[2] = BUTTON_3;
    buttonPins[3] = BUTTON_4;
    buttonPins[4] = BUTTON_5;
    buttonPins[5] = BUTTON_6;
    
    for (int i = 0; i < 6; i++) {
      pinMode(buttonPins[i], INPUT_PULLUP);
      buttonStates[i] = false;
      lastButtonStates[i] = false;
      lastDebounceTime[i] = 0;
    }
  }
  
  // Atualiza estado de todos os botões com debounce
  void update() {
    unsigned long currentTime = millis();
    
    for (int i = 0; i < 6; i++) {
      boolean reading = !digitalRead(buttonPins[i]); // Invertido (PULL-UP)
      
      if (reading != lastButtonStates[i]) {
        lastDebounceTime[i] = currentTime;
      }
      
      if (currentTime - lastDebounceTime[i] >= DEBOUNCE_TIME) {
        buttonStates[i] = reading;
      }
      
      lastButtonStates[i] = reading;
    }
  }
  
  // Retorna se botão está pressionado
  boolean isPressed(int buttonNum) {
    if (buttonNum < 0 || buttonNum > 5) return false;
    return buttonStates[buttonNum];
  }
  
  // Detecta transição (borda de subida do botão)
  boolean wasPressed(int buttonNum, boolean& lastState) {
    boolean currentState = isPressed(buttonNum);
    if (currentState && !lastState) {
      return true;  // Botão pressionado
    }
    lastState = currentState;
    return false;
  }
};

#endif
