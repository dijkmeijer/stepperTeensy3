#ifndef PARSER_HPP
#define PARSER_HPP

#include "conf.h"
#include <GCodeParser.h>
#include "motor.hpp"
#include "board.hpp"

#include <GCodeParser.h>

#ifndef PARSER_DECLS
# define _DECL extern
# define _INIT(x)
#else
# define _DECL
# define _INIT(x)  = x
#endif

_DECL GCodeParser GCode _INIT(GCodeParser());

int getCode(char , GCodeParser *);
int execGcode( c_motor **, GCodeParser *);

uint8_t end();

#endif