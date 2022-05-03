#include <Arduino.h>
/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper
 * motor in alternating directions.
 */
#define BOARD_DECLS
#include "board.hpp"
#define PARSER_DECLS
#include "parser.hpp"

#include "motor.hpp"
#include "conf.h"

// controller voor het aansturen van de verschillende motoren
StepControl controller; // Use default settings
RotateControl Rcontroller;


void setup()
{

  Serial.begin(115200);    // communicatie via USB<->serial
  Serial1.begin(115200); // HW UART drivers voor motor 1..4
  Serial2.begin(115200); // HW UART drivers voor motor 5..8

  initMCP(); // init MCP23008 IO expanders

  // definieer nieuwe motoren met TMC2209->config via serial, MCP voor driver enable, Stepperdrivers
  m[0] = new c_motor(&Serial1, MOTOR1_ADRESS, &mcp1, MOTOR1_ENABLE, M1_STEP_PIN, M1_DIR_PIN);
  m[1] = new c_motor(&Serial1, MOTOR2_ADRESS, &mcp1, MOTOR2_ENABLE, M2_STEP_PIN, M2_DIR_PIN);
  m[2] = new c_motor(&Serial1, MOTOR3_ADRESS, &mcp1, MOTOR3_ENABLE, M3_STEP_PIN, M3_DIR_PIN);
  m[3] = new c_motor(&Serial1, MOTOR4_ADRESS, &mcp1, MOTOR4_ENABLE, M4_STEP_PIN, M4_DIR_PIN); 

  m[4] = new c_motor(&Serial2, MOTOR5_ADRESS, &mcp3, MOTOR5_ENABLE, M5_STEP_PIN, M5_DIR_PIN);
  m[5] = new c_motor(&Serial2, MOTOR6_ADRESS, &mcp3, MOTOR6_ENABLE, M6_STEP_PIN, M6_DIR_PIN);
  m[6] = new c_motor(&Serial2, MOTOR7_ADRESS, &mcp3, MOTOR7_ENABLE, M7_STEP_PIN, M7_DIR_PIN);
  m[7] = new c_motor(&Serial2, MOTOR8_ADRESS, &mcp3, MOTOR8_ENABLE, M8_STEP_PIN, M8_DIR_PIN);
  // driver.pwm_autoscale(true); // Needed for stealthChop

   m[0]->setSpeed(500);
  // m[1]->setSpeed(19000);
  // m[2]->setSpeed(19000);
  // m[3]->setSpeed(19000);
  // m[4]->setSpeed(19000);
  // m[5]->setSpeed(19000);
  // m[6]->setSpeed(19000);
  // m[7]->setSpeed(19000);

  m[0]->setAcceleration(2000);
  m[1]->setAcceleration(2000);
  m[2]->setAcceleration(2000);
  m[3]->setAcceleration(2000);
  m[4]->setAcceleration(2000);
  m[5]->setAcceleration(2000);
  m[6]->setAcceleration(2000);
  
  m[0]->microstep(16);
  m[1]->microstep(16);
  m[2]->microstep(16);
  m[3]->microstep(16);
  m[4]->microstep(16);
  m[5]->microstep(16);
  m[6]->microstep(16);
  m[7]->microstep(16);

   m[0]->reverse();
   m[1]->reverse();

}

void loop()
{
  // m[0]->motor->setTargetRel(1600); // Set target position to 1000 steps from current position
  // m[1]->motor->setTargetRel(1600); // Set target position to 1000 steps from current position
  // m[2]->motor->setTargetRel(2080); // Set target position to 1000 steps from current position
  // m[3]->motor->setTargetRel(2080); // Set target position to 1000 steps from current position
  // m[4]->motor->setTargetRel(1600); // Set target position to 1000 steps from current position
  // m[5]->motor->setTargetRel(1600); // Set target position to 1000 steps from current position
  // m[6]->motor->setTargetRel(2080); // Set target position to 1000 steps from current position
  // m[7]->motor->setTargetRel(2080); // Set target position to 1000 steps from current position
  // // controller.move(*m[0]->motor, *m[1]->motor, *m[2]->motor, *m[3]->motor);         // Do the move
  //     controller.move(*m[0]->motor, *m[1]->motor, *m[2]->motor, *m[3]->motor, *m[4]->motor, *m[5]->motor, *m[6]->motor, *m[7]->motor); // Do the move

  // delay(20);
  


  if (Serial.available() > 0)
  {
       Rcontroller.rotateAsync(*m[0]->motor);
    Serial.println(Serial.available());

    if (GCode.AddCharToLine(Serial.read()))
    {

      GCode.ParseLine();
      // Code to process the line of G-Code here…

      Serial.print("Command Line: ");
      Serial.println(GCode.line);

      GCode.RemoveCommentSeparators();
      execGcode(m, &GCode);
      controller.moveAsync(*m[1]->motor, *m[2]->motor, *m[3]->motor, *m[4]->motor, *m[5]->motor, *m[6]->motor, *m[7]->motor); // Do the move
      while(controller.isRunning()) delay(0);
      Serial.println("ready");
    }
    
   }

}
