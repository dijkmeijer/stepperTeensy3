/*----------------------------------------------------------------------------
BOARD.H

Note: #define BOARD_DECLS 1 before including this file to DECLARE and INITIALIZE
global variables.  Include this file without defining BOARD_DECLS to extern
these variables.
----------------------------------------------------------------------------*/
#ifndef BOARD_DEFS          // Make sure this file is included only once
#define BOARD_DEFS 

#include "Adafruit_MCP23008.h"

#include "motor.hpp"
#include "conf.h"

/*----------------------------------------------
Setup variable declaration macros.
----------------------------------------------*/
#ifndef BOARD_DECLS
#pragma message("extern")
# define _DECL extern
# define _INIT(x)
#else
#pragma message("intern")
# define _DECL
# define _INIT(x)  = x
#endif

/*----------------------------------------------
Declare variables as follows:

_DECL [standard variable declaration] _INIT(x);

where x is the value with which to initialize
the variable.  If there is no initial value for
the variable, it may be declared as follows:

_DECL [standard variable declaration];
----------------------------------------------*/

// _DECL int var_a _INIT(100);
// _DECL int var_b;
// _DECL int var_c _INIT(27);

_DECL Adafruit_MCP23008 mcp1;
_DECL Adafruit_MCP23008 mcp2;
_DECL Adafruit_MCP23008 mcp3;
_DECL Adafruit_MCP23008 mcp4;

_DECL  c_motor *m[8];

uint8_t initMCP();

#endif
/*----------------------------------------------------------------------------
----------------------------------------------------------------------------*/