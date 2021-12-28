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
    Serial.print(P->line);
    if(getCode('G', P)==1){
        i = getCode('A', P);
        Serial.print("A = ");
        Serial.println(i);
        m[0]->motor->setTargetRel(i);
        
        i = getCode('B', P);
        Serial.print("B = ");
        Serial.println(i);
        m[1]->motor->setTargetRel(i);
        
        i = getCode('C', P);
        Serial.print("C = ");
        Serial.println(i);
        m[2]->motor->setTargetRel(i);

        i = getCode('V', P);
        Serial.print("V = ");
        Serial.println(i);
        m[3]->motor->setTargetRel(i);

        i = getCode('W', P);
        Serial.print("W = ");
        Serial.println(i);
        m[4]->motor->setTargetRel(i);
        
        i = getCode('X', P);
        Serial.print("X = ");
        Serial.println(i);
        m[5]->motor->setTargetRel(i);
        
        i = getCode('Y', P);
        Serial.print("Y = ");
        Serial.println(i);
        m[6]->motor->setTargetRel(i);
        
        i = getCode('Z', P);
        Serial.print("Z = ");
        Serial.println(i);
        m[7]->motor->setTargetRel(i);
      }
    return 0;
}