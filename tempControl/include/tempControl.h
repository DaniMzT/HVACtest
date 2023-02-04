#pragma once

//system status
//definition of errors (it could be done with enum, too) for system status
enum class systemInfo{
    SYSTEM_OK = 0, //system ok
    ERROR_UNDER_MIN = 1, //current sensor value under minimum threshold
    ERROR_OVER_MAX = 2, //current sensor value ove rmaximum threshold
    TEMP_NOT_REACHED = 3 //temperature not reached in a set time
    
};
extern systemInfo systemStatus; //to know if system is ok or there is an error. Global variable defined in .cpp

//Temperature status
enum class tempInfo{
    TEMP_OK = 0,
    TEMP_TOO_COLD = 1,
    TEMP_TOO_HOT = 2
};
extern tempInfo tempStatus; //temperature within limits or under/over. Global variable defined in .cpp


class Sensor {
    public:

    int sensitivity; //sensitivity: output [physical magnitude] / input [voltage]
    int offset; //sensor offset
    int min_limit; //minimum threshold
    int max_limit; //maximum threshold

    Sensor(int sens, int min, int max, int offset = 0); //constructor
    ~Sensor(); //destructor
} ;

class TempControl {
    public:

    Sensor tempSensor; //temperature sensor, an object of class Sensor. CONSTRUCT IT IN INITIALIZER LIST IN constructor 1 and 2
    int currentTemp; //current temperature
    int minTempSet; //minimum temperature set by user
    int maxTempSet; //maximum temperature set by user
    unsigned int set_time; //time set by user during which temperature should be within min_limit and max_limit
    unsigned int ini_time_ctrl; //time when control starts; used to warn TEMP_NOT_REACHED if time applying control is longer than set_time

    TempControl(Sensor tsensor, int minT, int maxT); //constructor 1
    TempControl(Sensor tsensor, int minT, int maxT, int setTime); //constructor 2
    ~TempControl(); //destructor

    void controlTemp(int rawInput, int curTime = 0); //get current temperature (rawInput ideally got from an interrupt) and, optionally, the current time
    void Cool(); //activate cool mechanism
    void HeatUp(); //activate heat up mechanism
    void SetTime(unsigned int setTime); //define set_time, especially if not defined in constructor 2 or changing its value on the fly
} ;
