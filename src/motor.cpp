// initialiseer motor met default waarden

#include "motor.hpp"
#include "conf.h"

#define R_SENSE 0.11f

c_motor::c_motor(){
    serialPort = &Serial1;
    R_sense = R_SENSE;
    serialAdres =  MOTOR1_ADRESS;
    
    stepPin = 5;
    dirPin = 4;
    enablePin = MOTOR1_ENABLE;
    

    init();
}

// initialiseer motor met seriele poort, mcp i2c adres, serieel adres van de tmc2209

c_motor::c_motor(HardwareSerial *_serialPort, Adafruit_MCP23008 *_mcpDriver,
    uint8_t _serial_adres, uint8_t _stepPin, uint8_t _dirPin, uint8_t _enablePin){
    serialPort = _serialPort;
    mcpDriver = _mcpDriver;
    serialAdres = _serial_adres;
    stepPin = _stepPin;
    dirPin = _dirPin;
    enablePin = _enablePin;
    R_sense = R_SENSE;
    motor = new Stepper(stepPin, dirPin);

    init();


}
//  c_motor(HardwareSerial *, uint8_t serialadres, Adafruit_MCP23008 *, uint8_t, uint8_t, Stepper *, uint8_t, uint8_t)
//  hardwareserial_X, mcpdriver*, MCPadres, enablePin,  stepper*, motorAdress, Stepin, dirPin)
c_motor::c_motor(HardwareSerial *_serialPort, uint8_t _serialadres,
                 Adafruit_MCP23008 *_mcpDriver, uint8_t _enablePin,
                 uint8_t _stepPin, uint8_t _dirPin){
    serialPort = _serialPort;
    mcpDriver = _mcpDriver;
    serialAdres = _serialadres;
    stepPin = _stepPin;
    dirPin = _dirPin;
    enablePin = _enablePin;

    R_sense = R_SENSE;
    motor = new Stepper(stepPin, dirPin);
    init();


}


uint8_t c_motor::init(){
    driver =  new TMC2209Stepper(serialPort, R_sense, serialAdres);
 
    
    // pinMode(stepPin, OUTPUT);
    // pinMode(dirPin, OUTPUT);   
    // mcpDriver->begin(MCP_1_ADRESS);
    mcpDriver->pinMode(enablePin, OUTPUT);
    mcpDriver->digitalWrite(enablePin, LOW);
    shaft = false;
    
    driver->begin();          // SPI:  Init CS pins and possible SW SPI pins
                           // UART: Init SW UART (if selected) with default 115200 baudrate
    driver->toff(3);          // Enables driver in software
    driver->rms_current(300); // Set motor RMS current
    driver->microsteps(4);    // Set microsteps to 1/16th

    motor->setMaxSpeed(5000).
        setAcceleration(40000); // steps/s^2
    return 0;
}

uint8_t c_motor::print(){
    // Serial.println(enablePin);
    // Serial.println(serialAdres);
    // Serial.println((int)mcpDriver);
    Serial.print(stepPin);
    Serial.print(" ");
    Serial.println(dirPin);
   return 0;
}

uint8_t c_motor::enable(uint8_t i)
{
    driver->toff(i); 
    return 0;
}

uint8_t c_motor::microstep(uint16_t n)
{
    driver->microsteps(n);
    return 0;
}

uint8_t c_motor::setSpeed(uint16_t s)
{
    motor->setMaxSpeed(s);
    return 0;
}

uint8_t c_motor::setAcceleration(uint16_t a)
{
    motor->setAcceleration(a);
    return 0;
}

uint8_t c_motor::reverse()
{
    shaft = !shaft;
    driver->shaft(shaft);
    return 0;
}
