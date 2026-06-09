#ifndef LOGIC_H
#define LOGIC_H

#include "config.h"
#include "relays.h"
#include "sensors.h"
#include "buttons.h"
#include "eeprom_config.h"

// ============================================
// LÓGICA DE CONTROLE - INTERTRAVAMENTO
// ============================================

class AccessLogic {
private:
  RelayController& relays;
  SensorController& sensors;
  ButtonController& buttons;
  EEPROMConfig& eeprom;
  
  boolean lastButtonState[6];
  boolean releaseButtonActive;
  unsigned long releaseActivationTime;
  
public:
  AccessLogic(RelayController& r, SensorController& s, ButtonController& b, EEPROMConfig& e)
    : relays(r), sensors(s), buttons(b), eeprom(e), releaseButtonActive(false) {
    for (int i = 0; i < 6; i++) {
      lastButtonState[i] = false;
    }
  }
  
  // Lê entradas de liberação geral
  void checkReleaseInputs() {
    boolean release1 = !digitalRead(RELEASE_1); // Ativo LOW
    boolean release2 = !digitalRead(RELEASE_2);
    
    if (release1 || release2) {
      if (!releaseButtonActive) {
        Serial.println("[LIBERAÇÃO GERAL ACIONADA]");
        relays.activateAll();
        releaseButtonActive = true;
        releaseActivationTime = millis();
      }
    }
  }
  
  // Aplica intertravamento e lógica condicional
  void processButtonInputs() {
    sensors.update();
    buttons.update();
    
    // ===== BOTÃO 1 =====
    if (buttons.wasPressed(0, lastButtonState[0])) {
      Serial.println("[BOTÃO 1 PRESSIONADO]");
      
      // Relé 1 pode abrir?
      if (!relays.isActive(1)) {  // Relé 2 não está ativo (não intertravado)
        // Sensor porta 2 está fechado?
        if (sensors.isClosed(1)) {  // Sensor 2 deve estar fechado
          relays.activate(0);  // Ativa Relé 1
          Serial.println("  -> Relé 1 ATIVADO (Sensor 2 fechado)");
        } else {
          Serial.println("  -> Negado: Sensor 2 está aberto");
        }
      } else {
        Serial.println("  -> Negado: Relé 2 está ativo (intertravado)");
      }
    }
    
    // ===== BOTÃO 2 =====
    if (buttons.wasPressed(1, lastButtonState[1])) {
      Serial.println("[BOTÃO 2 PRESSIONADO]");
      
      // Relé 2 pode abrir?
      if (!relays.isActive(0)) {  // Relé 1 não está ativo
        // Sensor porta 1 está fechado?
        if (sensors.isClosed(0)) {  // Sensor 1 deve estar fechado
          relays.activate(1);  // Ativa Relé 2
          Serial.println("  -> Relé 2 ATIVADO (Sensor 1 fechado)");
        } else {
          Serial.println("  -> Negado: Sensor 1 está aberto");
        }
      } else {
        Serial.println("  -> Negado: Relé 1 está ativo (intertravado)");
      }
    }
    
    // ===== BOTÃO 3 =====
    if (buttons.wasPressed(2, lastButtonState[2])) {
      Serial.println("[BOTÃO 3 PRESSIONADO]");
      
      if (!relays.isActive(3)) {
        if (sensors.isClosed(3)) {  // Sensor 4 deve estar fechado
          relays.activate(2);  // Ativa Relé 3
          Serial.println("  -> Relé 3 ATIVADO (Sensor 4 fechado)");
        } else {
          Serial.println("  -> Negado: Sensor 4 está aberto");
        }
      } else {
        Serial.println("  -> Negado: Relé 4 está ativo (intertravado)");
      }
    }
    
    // ===== BOTÃO 4 =====
    if (buttons.wasPressed(3, lastButtonState[3])) {
      Serial.println("[BOTÃO 4 PRESSIONADO]");
      
      if (!relays.isActive(2)) {
        if (sensors.isClosed(2)) {  // Sensor 3 deve estar fechado
          relays.activate(3);  // Ativa Relé 4
          Serial.println("  -> Relé 4 ATIVADO (Sensor 3 fechado)");
        } else {
          Serial.println("  -> Negado: Sensor 3 está aberto");
        }
      } else {
        Serial.println("  -> Negado: Relé 3 está ativo (intertravado)");
      }
    }
    
    // ===== BOTÃO 5 =====
    if (buttons.wasPressed(4, lastButtonState[4])) {
      Serial.println("[BOTÃO 5 PRESSIONADO]");
      
      if (!relays.isActive(5)) {
        if (sensors.isClosed(5)) {  // Sensor 6 deve estar fechado
          relays.activate(4);  // Ativa Relé 5
          Serial.println("  -> Relé 5 ATIVADO (Sensor 6 fechado)");
        } else {
          Serial.println("  -> Negado: Sensor 6 está aberto");
        }
      } else {
        Serial.println("  -> Negado: Relé 6 está ativo (intertravado)");
      }
    }
    
    // ===== BOTÃO 6 =====
    if (buttons.wasPressed(5, lastButtonState[5])) {
      Serial.println("[BOTÃO 6 PRESSIONADO]");
      
      if (!relays.isActive(4)) {
        if (sensors.isClosed(4)) {  // Sensor 5 deve estar fechado
          relays.activate(5);  // Ativa Relé 6
          Serial.println("  -> Relé 6 ATIVADO (Sensor 5 fechado)");
        } else {
          Serial.println("  -> Negado: Sensor 5 está aberto");
        }
      } else {
        Serial.println("  -> Negado: Relé 5 está ativo (intertravado)");
      }
    }
  }
  
  // Executa lógica de controle (deve ser chamado no loop principal)
  void update() {
    checkReleaseInputs();
    processButtonInputs();
    relays.update();
  }
};

#endif
