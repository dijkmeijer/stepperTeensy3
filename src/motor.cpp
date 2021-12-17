// initialiseer motor met default waarden

#include "motor.hpp"

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



    init();


}

uint8_t c_motor::init(){
    driver =  new TMC2209Stepper(serialPort, R_sense, serialAdres);
 
    motor = new Stepper(stepPin, dirPin);
    // pinMode(stepPin, OUTPUT);
    // pinMode(dirPin, OUTPUT);   
    // mcpDriver->begin(MCP_1_ADRESS);
    mcpDriver->pinMode(enablePin, OUTPUT);
    mcpDriver->digitalWrite(enablePin, LOW);
    
    
    // driver->begin();          // SPI:  Init CS pins and possible SW SPI pins
    //                        // UART: Init SW UART (if selected) with default 115200 baudrate
    // driver->toff(3);          // Enables driver in software
    // driver->rms_current(300); // Set motor RMS current
    // driver->microsteps(4);    // Set microsteps to 1/16th

    motor->setMaxSpeed(200).
        setAcceleration(1000); // steps/s^2
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

