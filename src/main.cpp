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
#include "parser.hpp"
#include "board.hpp"

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


   m[0] = new c_motor(&SERIAL_PORT, &mcp1, MOTOR1_ADRESS, &M1, MOTOR1_ENABLE);
   m[1] = new c_motor(&SERIAL_PORT, &mcp1, MOTOR2_ADRESS, &M2, MOTOR2_ENABLE);
   m[2] = new c_motor(&SERIAL_PORT, &mcp1, MOTOR3_ADRESS, &M3, MOTOR3_ENABLE);
   m[3] = new c_motor(&SERIAL_PORT, &mcp1, MOTOR4_ADRESS, &M4, MOTOR4_ENABLE);
  // driver.pwm_autoscale(true); // Needed for stealthChop

  m[0]->setSpeed(800);
  m[1]->setSpeed(800);
  m[2]->setSpeed(800);
  m[3]->setSpeed(800);
  m[0]->setAcceleration(2500);
  m[1]->setAcceleration(2500);
  m[2]->setAcceleration(2500);
  m[3]->setAcceleration(2500);
}

bool shaft = false;
void loop()
{
  m[0]->microstep(16);
  m[1]->microstep(16);
  m[2]->microstep(4);
  m[3]->microstep(4);
  M1.setTargetRel(3200); // Set target position to 1000 steps from current position
  M2.setTargetRel(3200); // Set target position to 1000 steps from current position
  M3.setTargetRel(4160); // Set target position to 1000 steps from current position
  M4.setTargetRel(4160); // Set target position to 1000 steps from current position
  controller.move(M1, M2, M3, M4);         // Do the move
  delay(20);
  m[0]-> reverse();
  m[1]-> reverse();
  m[2]-> reverse();
  m[3]-> reverse();

}
 