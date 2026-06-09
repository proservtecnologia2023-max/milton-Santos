#ifndef RELAYS_H
#define RELAYS_H

#include "config.h"

// ============================================
// BIBLIOTECA DE CONTROLE DE RELÉS
// ============================================

class RelayController {
private:
  int relayPins[6];
  RelayState relayStates[6];
  int relayDuration; // tempo em ms
  
public:
  RelayController(int duration = RELAY_ON_TIME_MIN) : relayDuration(duration) {
    relayPins[0] = RELAY_1;
    relayPins[1] = RELAY_2;
    relayPins[2] = RELAY_3;
    relayPins[3] = RELAY_4;
    relayPins[4] = RELAY_5;
    relayPins[5] = RELAY_6;
    
    // Inicializa estados
    for (int i = 0; i < 6; i++) {
      relayStates[i].isActive = false;
      relayStates[i].activationTime = 0;
      relayStates[i].duration = relayDuration;
      pinMode(relayPins[i], OUTPUT);
      digitalWrite(relayPins[i], HIGH); // Relé desativado (lógica invertida)
    }
  }
  
  // Ativa um relé por tempo definido
  void activate(int relayNum) {
    if (relayNum < 0 || relayNum > 5) return;
    relayStates[relayNum].isActive = true;
    relayStates[relayNum].activationTime = millis();
    relayStates[relayNum].duration = relayDuration;
    digitalWrite(relayPins[relayNum], LOW); // Ativa (lógica invertida)
  }
  
  // Desativa um relé imediatamente
  void deactivate(int relayNum) {
    if (relayNum < 0 || relayNum > 5) return;
    relayStates[relayNum].isActive = false;
    digitalWrite(relayPins[relayNum], HIGH); // Desativa
  }
  
  // Ativa todos os 6 relés (liberação geral)
  void activateAll() {
    for (int i = 0; i < 6; i++) {
      activate(i);
    }
  }
  
  // Desativa todos os relés
  void deactivateAll() {
    for (int i = 0; i < 6; i++) {
      deactivate(i);
    }
  }
  
  // Verifica se relé está ativo
  boolean isActive(int relayNum) {
    if (relayNum < 0 || relayNum > 5) return false;
    return relayStates[relayNum].isActive;
  }
  
  // Atualiza duração dos relés
  void setDuration(int durationMs) {
    relayDuration = durationMs;
  }
  
  // Processa timeouts dos relés (deve ser chamado no loop)
  void update() {
    unsigned long currentTime = millis();
    
    for (int i = 0; i < 6; i++) {
      if (relayStates[i].isActive) {
        if (currentTime - relayStates[i].activationTime >= relayStates[i].duration) {
          deactivate(i);
        }
      }
    }
  }
  
  // Imprime status de todos os relés
  void printStatus() {
    Serial.println("\n=== STATUS DOS RELÉS ===");
    for (int i = 0; i < 6; i++) {
      Serial.print("Relé ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(relayStates[i].isActive ? "ATIVO" : "INATIVO");
    }
    Serial.println("========================\n");
  }
};

#endif
