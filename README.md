# Controlador de Acesso 12V com 6 Relés Independentes

## 📋 Descrição do Projeto

Placa controladora de acesso 12V profissional com 6 relés independentes para controle de fechaduras eletromagnéticas e eletroímãs. Inclui intertravamento em pares, sensor de porta com lógica configurável (NF/NA), botoeiras de acionamento e liberação geral por contato seco.

## ✨ Características Principais

### **Entradas:**
- ✅ 6 Entradas de botoeira (24V tolerante)
- ✅ 6 Entradas de sensor de porta (configurável NF/NA via DIP Switch)
- ✅ 2 Entradas de liberação geral (contato seco)
- ✅ Proteção contra inversão de polaridade
- ✅ Proteção por fusível 20A

### **Saídas:**
- ✅ 6 Relés 12V/10A independentes (bornes plugáveis)
- ✅ Saída 12V regulada para carregador de bateria 40Ah
- ✅ LEDs de status (Alimentação, Relés, Sensores)

### **Controle e Lógica:**
- ✅ Intertravamento em pares: (1-2), (3-4), (5-6)
- ✅ Tempo de acionamento: 3-10s (DIP Switch/Jumper configurável)
- ✅ Lógica condicional: 
  - Botoeira 1 → Relé 1 abre apenas se porta 2 estiver fechada
  - Botoeira 2 → Relé 2 abre apenas se porta 1 estiver fechada
  - Padrão repetido para pares 3-4 e 5-6
- ✅ Liberação geral: Aciona todos os 6 relés ignorando intertravamento

### **Alimentação e Proteção:**
- ✅ Entrada 12V DC (bornes plugáveis)
- ✅ Saída 12V para carregador de bateria 40Ah
- ✅ Proteção contra inversão de polaridade (diodo Schottky)
- ✅ Fusível de proteção principal 20A
- ✅ Fusível por grupo de relés (opcional)

---

## 🔌 Pinagem e Conectores

### **Entrada de Alimentação (12V):**
```
┌─────────────────┐
│  ALIMENTAÇÃO    │
├─────────────────┤
│ + │ GND │ - │   │
└─────────────────┘
```

### **Botoeiras (IN1-IN6):**
Entrada ativa BAIXA (0V quando pressionado)
- Proteção contra transientes (filtro RC)
- Pull-up interno 10kΩ

### **Sensores de Porta (SENSOR1-6):**
- Configurável NF (Normalmente Fechado) ou NA (Normalmente Aberto) via DIP Switch
- Protegido contra transientes

### **Liberação Geral (LIB1, LIB2):**
- Contato seco (qualquer polaridade)
- Ativa LOW no microcontrolador

### **Relés de Saída (RELAY1-6):**
```
┌──────────────┐
│ NO  COM  NC  │ ← Para cada relé
└──────────────┘
```

---

## 🎛️ Configuração de DIP Switch / Jumper

### **Tempo de Acionamento (Switch 1-3):**
```
Posição │ Tempo (segundos)
─────────────────────────
 000    │ 3s
 001    │ 4s
 010    │ 5s
 011    │ 6s
 100    │ 7s
 101    │ 8s
 110    │ 9s
 111    │ 10s
```

### **Configuração Sensores NF/NA (Switch 4-9):**
```
Switch │ Sensor │ Configuração
───────┼────────┼──────────────
  4    │   1    │ 0=NF, 1=NA
  5    │   2    │ 0=NF, 1=NA
  6    │   3    │ 0=NF, 1=NA
  7    │   4    │ 0=NF, 1=NA
  8    │   5    │ 0=NF, 1=NA
  9    │   6    │ 0=NF, 1=NA
```

---

## 📊 Lógica de Funcionamento

### **Intertravamento Condicional:**

#### **Par 1-2:**
```
Botoeira 1 pressionada?
  └─→ Relé 1 pode abrir?
      └─→ SIM: Sensor porta 2 está fechado?
              └─→ SIM: Ativa Relé 1 por X segundos
              └─→ NÃO: Nega acionamento
      └─→ NÃO: Relé 2 está ativo?
              └─→ SIM: Nega acionamento (intertravado)
              └─→ NÃO: Ativa Relé 1 por X segundos

Botoeira 2 pressionada?
  └─→ Relé 2 pode abrir?
      └─→ SIM: Sensor porta 1 está fechado?
              └─→ SIM: Ativa Relé 2 por X segundos
              └─→ NÃO: Nega acionamento
      └─→ NÃO: Relé 1 está ativo?
              └─→ SIM: Nega acionamento (intertravado)
              └─→ NÃO: Ativa Relé 2 por X segundos
```

**Mesma lógica aplica para pares 3-4 e 5-6.**

### **Liberação Geral:**
```
Entrada LIB1 ou LIB2 ativada?
  └─→ SIM: Ativa TODOS os 6 relés por X segundos
           (Ignora intertravamento e sensores de porta)
           └─→ Decorrido tempo: Desativa todos
```

---

## 🛠️ Arquivos do Projeto

```
milton-Santos/
├── README.md                           # Este arquivo
├── docs/
│   ├── ESPECIFICACAO_TECNICA.md       # Especificação detalhada
│   ├── MANUAL_INSTALACAO.md           # Guia de instalação
│   ├── MANUAL_CONFIGURACAO.md         # Configuração DIP Switch
│   └── TROUBLESHOOTING.md             # Solução de problemas
├── firmware/
│   ├── main.ino                        # Código principal (Arduino)
│   ├── config.h                        # Configurações
│   ├── relays.h                        # Biblioteca de relés
│   ├── sensors.h                       # Biblioteca de sensores
│   ├── logic.h                         # Lógica de controle
│   └── eeprom_config.h                # Configuração EEPROM
├── hardware/
│   ├── schematics/
│   │   ├── power_supply.sch           # Alimentação e proteção
│   │   ├── relays.sch                 # Circuito dos relés
│   │   ├── inputs.sch                 # Entradas (botoeiras, sensores)
│   │   ├── microcontroller.sch        # Microcontrolador
│   │   └── full_schematic.sch         # Esquemático completo
│   ├── pcb/
│   │   ├── layout_recommendations.md  # Recomendações de layout
│   │   └── gerber_notes.md            # Notas para fabricação
│   └── 3d_model/
│       ├── enclosure_recommendations.md
│       └── connector_specifications.md
├── test/
│   ├── test_relays.ino                # Testes dos relés
│   ├── test_inputs.ino                # Testes de entradas
│   └── test_logic.ino                 # Testes da lógica
├── tools/
│   ├── dip_switch_calculator.py       # Calculadora de DIP Switch
│   └── configuration_helper.py        # Auxiliar de configuração
└── LICENSE                             # Licença do projeto
```

---

## 🚀 Quick Start

### **1. Hardware:**
1. Montar a PCB conforme esquemático
2. Conectar alimentação 12V
3. Instalar DIP Switch conforme necessário

### **2. Firmware:**
1. Abrir `firmware/main.ino` no Arduino IDE
2. Configurar placa (Arduino Mega, STM32, etc)
3. Fazer upload do código
4. Testar funcionalidades

### **3. Configuração:**
1. Ajustar DIP Switch para tempo desejado
2. Configurar sensores NF/NA
3. Testar botoeiras e liberação geral

---

## 📝 Especificações Técnicas Resumidas

| Parâmetro | Especificação |
|-----------|---------------|
| **Alimentação** | 12V DC ±10% |
| **Consumo máximo** | ~5A (todos relés ligados) |
| **Relés** | 6x 12V/10A (JQC-3F) |
| **Entradas** | 8 digitais (botoeiras + sensores + liberação) |
| **Proteção** | Fusível 20A + Diodo Schottky |
| **Temperatura operação** | -10°C a +60°C |
| **Umidade** | 10% a 90% (não condensante) |
| **Dimensões** | 200x150x80mm (estimado) |
| **Microcontrolador** | Arduino Mega 2560 ou STM32F103 |

---

## 📞 Suporte

Para dúvidas, sugestões ou contribuições, abra uma **Issue** no repositório.

---

## 📄 Licença

Este projeto é licenciado sob a Licença MIT. Veja o arquivo `LICENSE` para detalhes.

---

**Versão:** 1.0.0  
**Última atualização:** 2026-06-09  
**Mantenedor:** ProServ Tecnologia