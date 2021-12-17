#include <Arduino.h>
/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper
 * motor in alternating directions.
 */

#include <TMCStepper.h>
#include "Adafruit_MCP23008.h"
#include "TeensyStep.h"
#include "motor.hpp"
#include "conf.h"

Adafruit_MCP23008 mcp1;
Adafruit_MCP23008 mcp2;
Adafruit_MCP23008 mcp3;
Adafruit_MCP23008 mcp4;

c_motor *m[8];
Stepper *s[2]; 

//#define EN_PIN MOTOR1_ENABLE   // Enable
// #define DIR_PIN M1_DIR_PIN  // Direction
// #define STEP_PIN M1_STEP_PIN // Step
// #define ENABLE_MOTOR_1 MOTOR1_ENABLE
#define SERIAL_PORT Serial1 // TMC2208/TMC2224 HardwareSerial port
// #define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2

// Stepper motor(STEP_PIN, DIR_PIN); // STEP pin: 2, DIR pin: 3
// Stepper motor1(M2_STEP_PIN,  M2_DIR_PIN); // STEP pin: 2, DIR pin: 3
StepControl controller;           // Use default settings

#define R_SENSE 0.11f // Match to your driver                         
                      // SilentStepStick series use 0.11              
                      // UltiMachine Einsy and Archim2 boards use 0.2 
                      // Panucatt BSD2660 uses 0.1                    
                      // Watterott TMC5160 uses 0.075

#if SW_CAPABLE_PLATFORM
#pragma message("software serial")
#else
  #pragma message("hardware serial")
#endif

void setup()
{


  // pinMode(DIR_PIN, OUTPUT);
  // digitalWrite(EN_PIN, LOW); // Enable driver in hardware

  // Enable one according to your setup
  //SPI.begin();                    // SPI drivers
  Serial.begin(9600);
  SERIAL_PORT.begin(115200); // HW UART drivers
                             // driver.beginSerial(115200);     // SW UART drivers
  // m[0] = new c_motor;
  //mcp = new Adafruit_MCP23008; 
  mcp1.begin(MCP_1_ADRESS);
 mcp2.begin(MCP_2_ADRESS);
 mcp3.begin(MCP_3_ADRESS);
 mcp4.begin(MCP_4_ADRESS);
delay(5000);
  Serial.println("begin");
  Serial.println(int(&mcp1));
  Serial.println(int(&mcp2));
  Serial.println(int(&mcp3));
  Serial.println(int(&mcp4));
  
   m[0] = new c_motor(&SERIAL_PORT, &mcp1, MOTOR1_ADRESS, M1_STEP_PIN, M1_DIR_PIN, MOTOR1_ENABLE);
   m[1] = new c_motor(&SERIAL_PORT, &mcp1, MOTOR2_ADRESS, M2_STEP_PIN, M2_DIR_PIN, MOTOR2_ENABLE);
   m[0]->motor;// driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
   m[1]->motor;// driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
  // driver.pwm_autoscale(true); // Needed for stealthChop

}

bool shaft = false;

void loop()
{
  // // Run 5000 steps and switch direction in software
  // for (uint16_t i = 5000; i > 0; i--)
  // {
  //   digitalWrite(STEP_PIN, HIGH);
  //   delayMicroseconds(100);
  //   digitalWrite(STEP_PIN, LOW);
  //   delayMicroseconds(100);
  // }
  // shaft = !shaft;
  // driver.shaft(shaft);
  // m[0]->motor->setTargetAbs (5.18 * 800); // Set target position to 1000 steps from current position
  // m[1]->motor->setTargetAbs(2.59 * 800); // Set target position to 1000 steps from current position
  m[0]->motor->setTargetRel( 800); // Set target position to 1000 steps from current position
  m[1]->motor->setTargetRel( 800); // Set target position to 1000 steps from current position
  controller.move(m[0]->motor, m[1]->motor);         // Do the move
delay(1000);
  //     Serial.println(int(&mcp));
  //     mcp.pinMode(0, OUTPUT);
  //     mcp.digitalWrite(0, HIGH);
  //     mcp.pinMode(3, OUTPUT);
  //     mcp.digitalWrite(3, HIGH);
  // delay(2000);
  //     mcp.pinMode(0, OUTPUT);
  //     mcp.digitalWrite(0, LOW);
  //     mcp.pinMode(3, OUTPUT);
  //     mcp.digitalWrite(3, LOW);
  // shaft = !shaft;
  // driver.shaft(shaft);
}
