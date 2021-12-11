// initialiseer motor met default waarden

#include "motor.hpp"

#define R_SENSE 0.11f



c_motor::c_motor(){
    stepPin = 5;
    dirPin = 4;
    setAdres(&Serial1, 0x25, 0);
    R_sense = R_SENSE;
    driver =  new TMC2209Stepper(serialPort, R_sense, serialAdres);
    motor = new Stepper(stepPin, dirPin);
}

// initialiseer motor met seriele poort, mcp i2c adres, serieel adres van de tmc2209

c_motor::c_motor(comm * _comm,
    uint8_t _mcp_adres, uint8_t _serial_adres, uint8_t _stepPin, uint8_t _dirPin, uint8_t _enablePin){
    stepPin = _stepPin;
    dirPin = _dirPin;
    enablePin = _enablePin;
    R_sense = R_SENSE;
    setAdres(_comm->serport, _mcp_adres, _serial_adres);
    setMCP(_comm->mcpDriver, _comm->mcpGpio);
    driver =  new TMC2209Stepper(serialPort, R_sense, serialAdres);
    motor = new Stepper(stepPin, dirPin);
}

// set tijdens of verander adresgegevens van de motor driver na initialisatie
int c_motor::setAdres(Stream * _serport, uint8_t _mcp_adres, uint8_t _serial_adres){
    mcpAdres = _mcp_adres;
    serialAdres = _serial_adres;
    serialPort = _serport;
    return 0;
};

int c_motor::setMCP(Adafruit_MCP23008 * _mcpDriver, Adafruit_MCP23008 * _mcpGpio){
    mcp_driver = _mcpDriver;
    mcp_GPIO = _mcpGpio;
    return 0;
}