#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// CONFIGURAÇÃO - CONTROLADOR 6 RELÉS 12V
// ============================================

// ---- PINOS ARDUINO ----
#define BUTTON_1  2
#define BUTTON_2  3
#define BUTTON_3  4
#define BUTTON_4  5
#define BUTTON_5  6
#define BUTTON_6  7

#define SENSOR_1  8
#define SENSOR_2  9
#define SENSOR_3  10
#define SENSOR_4  11
#define SENSOR_5  12
#define SENSOR_6  13

#define RELEASE_1 A0
#define RELEASE_2 A1

#define RELAY_1   22
#define RELAY_2   23
#define RELAY_3   24
#define RELAY_4   25
#define RELAY_5   26
#define RELAY_6   27

#define LED_POWER A2
#define LED_STATUS A3

// ---- PINOS DIP SWITCH (entrada analógica) ----
#define DIP_SWITCH_PIN A4

// ---- CONSTANTES DE TEMPO ----
#define DEBOUNCE_TIME 20  // ms
#define RELAY_ON_TIME_MIN 3000   // 3 segundos em ms
#define RELAY_ON_TIME_MAX 10000  // 10 segundos em ms

// ---- CONFIGURAÇÃO EEPROM ----
#define EEPROM_ADDR_TIME_CONFIG 0
#define EEPROM_ADDR_SENSOR_NF_NA 1

// ---- ESTRUTURA DE DADOS ----
struct RelayState {
  boolean isActive;
  unsigned long activationTime;
  int duration; // em ms
};

struct SensorState {
  boolean isNF;  // true = Normalmente Fechado, false = Normalmente Aberto
  boolean isClosed;
};

#endif
