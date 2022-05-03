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
    int i;
    if(getCode('G', P)==1){
        i = getCode('A', P);
        m[0]->motor->setTargetAbs(i);
        
        i = getCode('B', P);
        m[1]->motor->setTargetAbs(i);
        
        i = getCode('C', P);
        m[2]->motor->setTargetAbs(i);

        i = getCode('V', P);
        m[3]->motor->setTargetAbs(i);

        i = getCode('W', P);
        m[4]->motor->setTargetAbs(i);
        
        i = getCode('X', P);
        m[5]->motor->setTargetAbs(i);
        
        i = getCode('Y', P);
        m[6]->motor->setTargetAbs(i);
        
        i = getCode('Z', P);
        m[7]->motor->setTargetAbs(i);
      }
    return 0;
}