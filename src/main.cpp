/*
 Copyright (c) 2022 Valentijn

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <Arduino.h>


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

  
  m[0]->microstep(16);
  m[1]->microstep(16);
 

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
  


    Serial.println(Serial.available());


      controller.moveAsync(*m[1]->motor, *m[2]->motor); // Do the move
      while(controller.isRunning()) delay(0);
      Serial.println("ready");
    

}
