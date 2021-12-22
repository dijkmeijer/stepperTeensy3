#ifndef CONF_H
#define CONF_H

// Step en Dir pins van de diverse TCM2209 drivers

#define M1_DIR_PIN  5
#define M1_STEP_PIN 4
#define M2_DIR_PIN  11
#define M2_STEP_PIN 8
#define M3_DIR_PIN  2
#define M3_STEP_PIN 3
#define M4_DIR_PIN  7
#define M4_STEP_PIN 6
#define M5_DIR_PIN  17
#define M5_STEP_PIN 16
#define M6_DIR_PIN  14
#define M6_STEP_PIN 15
#define M7_DIR_PIN  21
#define M7_STEP_PIN 20
#define M8_DIR_PIN  23
#define M8_STEP_PIN 22

//  Serial pins, wordt automatisch geconfigureerd

#define SERIAL1_TX_PIN 0
#define SERIAL1_RX_PIN 1
#define SERIAL2_TX_PIN 9
#define SERIAL2_RX_PIN 10

// i2c Pins, wordt automatisch geconfigureerd

#define SCL_PIN     19
#define SDA_PIN     18

// mcp interrupt pins, moeten worden voorzien van interrupt routine 
// in geval van ingangen op de MCP23008

#define INTERRUPT_1_A_PIN 29    // op i2c adres 25
#define INTERRUPT_1_B_PIN 30    // op i2c adres 20
#define INTERRUPT_2_A_PIN 27    // op i2c adres 24
#define INTERRUPT_2_B_PIN 28    // op i2c adres 21

//???????????????????????????????????????????????????????????
// i2c adressen checken
//???????????????????????????????????????????????????????????

// mcp ADRESSEN van de diverse mcp32008 i/o expanders
// mcp1 en mcp3 zijn verbonden met de enable pins van de TCM2209 stepper drivers
// mcp1 en mcp3 Kunnen worden verbonden met eindstops
// mcp2 en mcp4 Kunnen worden gebruikt al GPIO

#define MCP_1_ADRESS 0x25 
#define MCP_2_ADRESS 0x20 

#define MCP_3_ADRESS 0x24 
#define MCP_4_ADRESS 0x21

#define IO_A 25

// serial adress for TCM2209 motordrivers

#define MOTOR1_ADRESS 0b00
#define MOTOR2_ADRESS 0b11
#define MOTOR3_ADRESS 0b01
#define MOTOR4_ADRESS 0b10
#define MOTOR5_ADRESS 0b00
#define MOTOR6_ADRESS 0b11
#define MOTOR7_ADRESS 0b10
#define MOTOR8_ADRESS 0b10

// mcp pins voor enablen van de TCM2209 motordrivers

#define MOTOR1_ENABLE 0
#define MOTOR2_ENABLE 1  // aanpassing gemeten
#define MOTOR3_ENABLE 2
#define MOTOR4_ENABLE 3
#define MOTOR5_ENABLE 0
#define MOTOR6_ENABLE 1
#define MOTOR7_ENABLE 2
#define MOTOR8_ENABLE 3

// MCP pinnen voor GPIO extention

#define IO_00 4
#define IO_01 5
#define IO_02 6
#define IO_03 7
#define IO_04 0
#define IO_05 1
#define IO_06 2
#define IO_07 3
#define IO_08 4
#define IO_09 5
#define IO_10 6
#define IO_11 7

#define IO_12 4
#define IO_13 5
#define IO_14 6
#define IO_15 7
#define IO_16 0
#define IO_17 1
#define IO_18 2
#define IO_19 3
#define IO_20 4
#define IO_21 5
#define IO_22 6
#define IO_23 7

#endif