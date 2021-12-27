#include "parser.hpp"

int getCode(char c, GCodeParser *P)
{
    	int value;
      if (GCode.HasWord(c))
      {
        value = (int)GCode.GetWordValue(c);
        return value;
      }  
      return -1;    
}

int execGcode(c_motor **m, GCodeParser *P){
    if(getCode('G', P)==1){
        
        m[0]->motor->setTargetRel(getCode('A', P));
        m[1]->motor->setTargetRel(getCode('B', P));
        m[2]->motor->setTargetRel(getCode('C', P));
        m[3]->motor->setTargetRel(getCode('D', P));
      }
    return 0;
}