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

void setup()
{

  Serial.begin(9600);    // communicatie via USB<->serial
  Serial1.begin(115200); // HW UART drivers voor motor 1..4
  Serial2.begin(115200); // HW UART drivers voor motor 5..8

  initMCP(); // init MCP23008 IO expanders

  // definieer nieuwe motoren met TMC2209->config via serial, MCP voor driver enable, Stepperdrivers
  m[0] = new c_motor(&Serial1, MOTOR1_ADRESS, &mcp1, MOTOR1_ENABLE, M1_STEP_PIN, M1_DIR_PIN);
  m[1] = new c_motor(&Serial1, MOTOR2_ADRESS, &mcp1, MOTOR2_ENABLE, M2_STEP_PIN, M2_DIR_PIN);
  m[2] = new c_motor(&Serial1, MOTOR3_ADRESS, &mcp1, MOTOR3_ENABLE, M3_STEP_PIN, M3_DIR_PIN);
  m[3] = new c_motor(&Serial1, MOTOR4_ADRESS, &mcp1, MOTOR4_ENABLE, M4_STEP_PIN, M4_DIR_PIN);

  // driver.pwm_autoscale(true); // Needed for stealthChop

  m[0]->setSpeed(1900);
  m[1]->setSpeed(1900);
  m[2]->setSpeed(1900);
  m[3]->setSpeed(1900);
  m[0]->setAcceleration(1700);
  m[1]->setAcceleration(1700);
  m[2]->setAcceleration(1700);
  m[3]->setAcceleration(1700);
  m[0]->microstep(16);
  m[1]->microstep(16);
  m[2]->microstep(16);
  m[3]->microstep(16);
   m[2]->reverse();
   m[3]->reverse();
}

void loop()
{
  // m[0]->motor->setTargetRel(1600); // Set target position to 1000 steps from current position
  // m[1]->motor->setTargetRel(1600); // Set target position to 1000 steps from current position
  // m[2]->motor->setTargetRel(2080); // Set target position to 1000 steps from current position
  // m[3]->motor->setTargetRel(2080); // Set target position to 1000 steps from current position
  // controller.move(*m[0]->motor, *m[1]->motor, *m[2]->motor, *m[3]->motor);         // Do the move

  // Serial.println("ready");
  delay(20);
  // m[0]->reverse();
  // m[1]->reverse();
  // m[2]->reverse();
  // m[3]->reverse();
  if (Serial.available() > 0)
  {
    if (GCode.AddCharToLine(Serial.read()))
    {
      GCode.ParseLine();
      // Code to process the line of G-Code here…

      // Serial.print("Command Line: ");
      // Serial.println(GCode.line);

      GCode.RemoveCommentSeparators();
      execGcode(m, &GCode);
      controller.move(*m[0]->motor, *m[1]->motor, *m[2]->motor, *m[3]->motor); // Do the move
      Serial.println("ready");
    }
    
  }

}
