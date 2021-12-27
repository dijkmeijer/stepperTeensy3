#ifndef MOTOR_HPP
#define MOTOR_HPP

// alle waarden invullen met gedefinieerde waarde uit headerfile

#include <Arduino.h>

#include <TMCStepper.h>
#include "Adafruit_MCP23008.h"
#include "TeensyStep.h"

#include <HardwareSerial.h>
#include "conf.h"



class c_motor {
    public:
        c_motor();                                    //constructor
        c_motor(HardwareSerial *, Adafruit_MCP23008 *, uint8_t, uint8_t, uint8_t, uint8_t);         
                         // constructor met initialisatie seriele poort, mcp adres, serieel adres
                         // HardwareSerial * serialPort, Adafruit_MCP23008 *_mcpDriver, 
                         // uint8_t Serial adres, uint8_t mcp_driveradres,
                         // uint8_t dirPin, uint8_t stepPin, uint8_t MCP_enablePin  
        c_motor(HardwareSerial *, Adafruit_MCP23008 *, uint8_t,  Stepper *, uint8_t);
        c_motor(HardwareSerial *, uint8_t ,
                 Adafruit_MCP23008 *, uint8_t , 
                 uint8_t , uint8_t);
     // configuratie tmc2209 driver
        uint8_t print();
        uint8_t enable(uint8_t);
        uint8_t microstep(uint16_t);
        uint8_t setSpeed(uint16_t);
        uint8_t setAcceleration(uint16_t);
        uint8_t reverse();
        Stepper *motor;   // motor driver step / dir controle, public voor controller 

    private:
        uint8_t init();
        uint8_t stepPin;
        uint8_t dirPin;
        uint8_t enablePin;
        bool shaft;
        float R_sense;                  // ref weerstand motor stroom
        uint8_t serialAdres;            // serial adres van de motordriver
        HardwareSerial *serialPort;             // serial post voor driver configuratie
        Adafruit_MCP23008 *mcpDriver;  // i2c driver voor enable motordriver
        TMC2209Stepper *driver;    
};




#endif