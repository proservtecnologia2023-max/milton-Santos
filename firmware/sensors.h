#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"

// ============================================
// BIBLIOTECA DE LEITURA DE SENSORES
// ============================================

class SensorController {
private:
  int sensorPins[6];
  SensorState sensorStates[6];
  unsigned long lastDebounceTime[6];
  boolean lastReading[6];
  
public:
  SensorController() {
    sensorPins[0] = SENSOR_1;
    sensorPins[1] = SENSOR_2;
    sensorPins[2] = SENSOR_3;
    sensorPins[3] = SENSOR_4;
    sensorPins[4] = SENSOR_5;
    sensorPins[5] = SENSOR_6;
    
    // Inicializa sensores como NF (Normalmente Fechado)
    for (int i = 0; i < 6; i++) {
      pinMode(sensorPins[i], INPUT_PULLUP);
      sensorStates[i].isNF = true;  // Padrão: NF
      sensorStates[i].isClosed = true;
      lastReading[i] = true;
      lastDebounceTime[i] = 0;
    }
  }
  
  // Configura sensor como NF ou NA
  void setNF_NA(int sensorNum, boolean isNF) {
    if (sensorNum < 0 || sensorNum > 5) return;
    sensorStates[sensorNum].isNF = isNF;
  }
  
  // Lê estado do sensor com debounce
  void update() {
    unsigned long currentTime = millis();
    
    for (int i = 0; i < 6; i++) {
      boolean reading = digitalRead(sensorPins[i]);
      
      if (reading != lastReading[i]) {
        lastDebounceTime[i] = currentTime;
      }
      
      if (currentTime - lastDebounceTime[i] >= DEBOUNCE_TIME) {
        // Estado mudou
        if (sensorStates[i].isNF) {
          // Normalmente Fechado: LOW = fechado, HIGH = aberto
          sensorStates[i].isClosed = !reading;
        } else {
          // Normalmente Aberto: HIGH = fechado, LOW = aberto
          sensorStates[i].isClosed = reading;
        }
      }
      
      lastReading[i] = reading;
    }
  }
  
  // Retorna se porta está fechada
  boolean isClosed(int sensorNum) {
    if (sensorNum < 0 || sensorNum > 5) return false;
    return sensorStates[sensorNum].isClosed;
  }
  
  // Retorna se porta está aberta
  boolean isOpen(int sensorNum) {
    return !isClosed(sensorNum);
  }
  
  // Imprime status de todos os sensores
  void printStatus() {
    Serial.println("\n=== STATUS DOS SENSORES ===");
    for (int i = 0; i < 6; i++) {
      Serial.print("Sensor ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(sensorStates[i].isClosed ? "FECHADO" : "ABERTO");
      Serial.print(" (");
      Serial.print(sensorStates[i].isNF ? "NF" : "NA");
      Serial.println(")");
    }
    Serial.println("============================\n");
  }
};

#endif
