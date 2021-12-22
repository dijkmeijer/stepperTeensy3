#pragma once

#include <TMCStepper.h>
#include "Adafruit_MCP23008.h"
#include "TeensyStep.h"
#include "motor.hpp"
#include "conf.h"

Adafruit_MCP23008 mcp1;
Adafruit_MCP23008 mcp2;
Adafruit_MCP23008 mcp3;
Adafruit_MCP23008 mcp4;

Stepper M1(M1_STEP_PIN,M1_DIR_PIN);
Stepper M2(M2_STEP_PIN,M2_DIR_PIN);
Stepper M3(M3_STEP_PIN,M3_DIR_PIN);
Stepper M4(M4_STEP_PIN,M4_DIR_PIN);
c_motor *m[8];
