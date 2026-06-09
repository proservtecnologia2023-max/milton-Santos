#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

#include <EEPROM.h>
#include "config.h"

// ============================================
// CONFIGURAÇÃO EEPROM
// ============================================

class EEPROMConfig {
private:
  int baseAddress;
  
public:
  EEPROMConfig(int addr = 0) : baseAddress(addr) {}
  
  // Lê o tempo de acionamento (3-10 segundos) do DIP Switch
  int readRelayTimeFromDip() {
    int dipValue = analogRead(DIP_SWITCH_PIN);
    int timeSelection = (dipValue / 204); // 1024 / 5 = 204 (5 posições)
    if (timeSelection > 7) timeSelection = 7; // Limita a 10s
    
    int baseTime = RELAY_ON_TIME_MIN;
    return baseTime + (timeSelection * 1000); // +1s por posição
  }
  
  // Lê configuração NF/NA dos sensores
  boolean readSensorConfig(int sensorNum) {
    // sensorNum: 0-5 (sensor 1-6)
    // Aqui você pode ler de pinos DIP Switch adicionais
    // Por enquanto, retorna true (NF) por padrão
    return true;
  }
  
  // Salva configurações na EEPROM (opcional)
  void saveTimeConfig(int timeMs) {
    EEPROM.write(baseAddress + EEPROM_ADDR_TIME_CONFIG, (byte)(timeMs / 1000));
  }
  
  // Carrega configurações da EEPROM
  int loadTimeConfig() {
    byte timeSeconds = EEPROM.read(baseAddress + EEPROM_ADDR_TIME_CONFIG);
    if (timeSeconds < 3 || timeSeconds > 10) {
      return RELAY_ON_TIME_MIN; // Valor padrão
    }
    return timeSeconds * 1000;
  }
  
  // Imprime configuração para debug
  void printConfig() {
    Serial.println("\n=== CONFIGURAÇÃO ATUAL ===");
    Serial.print("Tempo de acionamento: ");
    Serial.print(readRelayTimeFromDip() / 1000);
    Serial.println(" segundos");
    Serial.println("============================\n");
  }
};

#endif
