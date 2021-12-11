#ifndef MOTOR_HPP
#define MOTOR_HPP

// alle waarden invullen met gedefinieerde waarde uit headerfile

#include <Arduino.h>

#include <TMCStepper.h>
#include "Adafruit_MCP23008.h"
#include "TeensyStep.h"

#include <Stream.h>
#include "conf.h"

class comm{
   public:
   Stream *serialPort;   
   Adafruit_MCP23008 *mcpDriver;
   Adafruit_MCP23008 *mcpGpio;
   comm();
};

class c_motor {
    public:
        c_motor();                                    //constructor
        c_motor(comm *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);         
                         // constructor met initialisatie seriele poort, mcp adres, serieel adres
        int setAdres(Stream *, uint8_t, uint8_t);   // Set communicatie gegevens: seriele poort, mcp adres, serieel adres
        int setMCP(Adafruit_MCP23008 *, Adafruit_MCP23008 *);       
        Stepper *motor;                 // motor driver step / dir controle
        TMC2209Stepper *driver;         // configuratie tmc2209 driver

    private:
        uint8_t stepPin;
        uint8_t dirPin;
        uint8_t enablePin;
        float R_sense;                  // ref weerstand motor stroom
        uint8_t mcpAdres;               // i2c adres voor enable motordriver 
        uint8_t serialAdres;            // serial adres van de motordriver
        Stream *serialPort;             // serial post voor driver configuratie
        Adafruit_MCP23008 *mcp_driver;  // i2c driver voor enable motordriver
        Adafruit_MCP23008 *mcp_GPIO;

};




#endif