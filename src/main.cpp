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

Adafruit_MCP23008 *mcp;
c_motor *m[8];

//#define EN_PIN MOTOR1_ENABLE   // Enable
#define DIR_PIN M1_DIR_PIN  // Direction
#define STEP_PIN M1_STEP_PIN // Step
#define ENABLE_MOTOR_1 MOTOR1_ENABLE
#define SERIAL_PORT Serial1 // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2

Stepper motor(STEP_PIN, DIR_PIN); // STEP pin: 2, DIR pin: 3
StepControl controller;           // Use default settings

#define R_SENSE 0.11f // Match to your driver                         
                      // SilentStepStick series use 0.11              
                      // UltiMachine Einsy and Archim2 boards use 0.2 
                      // Panucatt BSD2660 uses 0.1                    
                      // Watterott TMC5160 uses 0.075

// Select your stepper driver type
//TMC2130Stepper driver(CS_PIN, R_SENSE);                           // Hardware SPI
//TMC2130Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK); // Software SPI
//TMC2660Stepper driver(CS_PIN, R_SENSE);                           // Hardware SPI
//TMC2660Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);
//TMC5160Stepper driver(CS_PIN, R_SENSE);
//TMC5160Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS); // Hardware Serial
//TMC2208Stepper driver(SW_RX, SW_TX, R_SENSE);                     // Software serial
//TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2209Stepper driver(SW_RX, SW_TX, R_SENSE, DRIVER_ADDRESS);

void setup()
{

  mcp = new(Adafruit_MCP23008);
  mcp->begin(0x25); // use default address 0, 
  mcp->pinMode(ENABLE_MOTOR_1, OUTPUT);
  mcp->digitalWrite(ENABLE_MOTOR_1, LOW);

  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);

  m[0] = new c_motor(&SERIAL_PORT, mcp, mcp, 1,2,3,4,5); 
  m[1] = new c_motor;
  // pinMode(DIR_PIN, OUTPUT);
  // digitalWrite(EN_PIN, LOW); // Enable driver in hardware

  // Enable one according to your setup
  //SPI.begin();                    // SPI drivers
  SERIAL_PORT.begin(115200); // HW UART drivers
                             // driver.beginSerial(115200);     // SW UART drivers

  driver.begin();          // SPI:  Init CS pins and possible SW SPI pins
                           // UART: Init SW UART (if selected) with default 115200 baudrate
  driver.toff(3);          // Enables driver in software
  driver.rms_current(300); // Set motor RMS current
  driver.microsteps(4);    // Set microsteps to 1/16th

  // driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
  // driver.pwm_autoscale(true); // Needed for stealthChop
  m[0]->motor
      ->setMaxSpeed(2000)      // steps/s
      .setAcceleration(10000); // steps/s^2
  m[1]->motor
      ->setMaxSpeed(1000)      // steps/s
      .setAcceleration(10000); // steps/s^2
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
  m[0]->motor->setTargetRel(5.18 * 800); // Set target position to 1000 steps from current position
  m[1]->motor->setTargetRel(2.59 * 800); // Set target position to 1000 steps from current position
  controller.move(*m[0]->motor,*m[1]->motor);         // Do the move
  // // delay(2000);
  // shaft = !shaft;
  // driver.shaft(shaft);
}
