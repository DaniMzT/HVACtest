#include <stdio.h>
#include <thread> //for delays
#include <chrono> //for defining seconds in delays
#include "tempControl.h"

const int TEMP_SENSOR_SENSITIVITY = 2; //deg/V. I'm working in V instead of mV for the sake of simplicity
const int TEMP_SENSOR_MIN_V = 0; //V
const int TEMP_SENSOR_MAX_V = 24; //V

const int TEMP_MIN = 20; //deg in Celsius
const int TEMP_MAX = 22;
const int TEMP_TIME_ALLOWED = 120; //in seconds

int simulateTempSensor(int previousT); 

int main(){
    int curRaw_V = 1; //current data sensor (in V)
    unsigned int iterations = 0;

    //object for temperature sensor
    Sensor tSensor(TEMP_SENSOR_SENSITIVITY, TEMP_SENSOR_MIN_V, TEMP_SENSOR_MAX_V);
    //object for temperature control
    TempControl tControl(tSensor, TEMP_MIN, TEMP_MAX,TEMP_TIME_ALLOWED);

    while(1){ 
        //in an ideal solution with a uC, if possible I'd put the uC in low-power consumption until timer wakes it up. Here I'm doing polling mode with a delay
        tControl.controlTemp(curRaw_V, iterations);
        std::this_thread::sleep_for(std::chrono::seconds(2)); //polling mode
        iterations++;
        curRaw_V = simulateTempSensor(tControl.currentTemp);
    }
    return 0;
}
//here interrupt handlers and callbacks would be defined: interrupt handler when timer hits. Then, enable communication (with interrupts) to read temperature (curRaw_mV) 

// @brief Simulate output in mV from the temperature sensor. Increase or decrease temperature gradually until some limits hardcoded inside the function
// @param previousT: previous temperature value
// @return output (V) from temperature sensor (emulation)
int simulateTempSensor(int previousT){
    unsigned int highestDeviation = TEMP_MAX + 5;
    unsigned int lowestDeviation = TEMP_MIN - 5;
    int returnedValue = previousT/TEMP_SENSOR_SENSITIVITY; //no offset considered
    enum Tendency {COOLING, HEATING};
    static Tendency curTend = HEATING;
    if (curTend == HEATING){
        if (previousT < highestDeviation){
            returnedValue++;
        }
        else{ //highest function limit reached
            curTend = COOLING;
            returnedValue--;
        }
    }
    else{ //COOLING
        if (previousT > lowestDeviation){
            returnedValue--;
        }
        else{ //lowest function limit reached
            curTend = HEATING;
            returnedValue++;
        }
    }
    return returnedValue;
}