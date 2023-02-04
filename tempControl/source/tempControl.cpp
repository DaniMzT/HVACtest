#include "tempControl.h"
#include <iostream>
using namespace std;

systemInfo systemStatus = systemInfo::SYSTEM_OK;
tempInfo tempStatus = tempInfo::TEMP_OK;

//Class Sensor
Sensor::Sensor(int sens, int min, int max, int off){ //constructor
    sensitivity = sens;
    min_limit = min;
    max_limit = max;
    offset = off;
} 
Sensor::~Sensor(){ //destructor 
    cout << "Sensor object destructor";
}


//Class TempControl
TempControl::TempControl(Sensor tsensor, int minT, int maxT) : tempSensor(tsensor) { //constructor 1. : tempSensor(tsensor) is a required initializer list
    tempSensor = tsensor; 
    minTempSet = minT; 
    maxTempSet = maxT;
} 
TempControl::TempControl(Sensor tsensor, int minT, int maxT, int setTime) : tempSensor(tsensor) { //constructor 2.  tempSensor(tsensor) is a required initializer list
    tempSensor = tsensor; 
    minTempSet = minT; 
    maxTempSet = maxT;
    set_time = setTime; 
} 
TempControl::~TempControl(){ //destructor
    cout << "TempControl object destructor"<<endl;
} 

void TempControl::controlTemp(int rawInput, int curTime) {
    currentTemp = rawInput * tempSensor.sensitivity + tempSensor.offset;
    cout << "Temperature:" << currentTemp <<endl;
    //Sensor ok?
    if (rawInput < tempSensor.min_limit){
        systemStatus = systemInfo::ERROR_UNDER_MIN;
        cout << "Sensor value under limit" <<endl;
    }
    else if (rawInput > tempSensor.max_limit){
        systemStatus = systemInfo::ERROR_OVER_MAX;
        cout << "Sensor value over limit" <<endl;
    }
    else{
        systemStatus = systemInfo::SYSTEM_OK;
    }
    //Temperature ok? if not, Cool() or HeatUp()
    if (currentTemp < minTempSet){
        if (tempStatus == tempInfo::TEMP_OK) { //if previous temperature read had been ok, this is the beginning of a new temperature control
            ini_time_ctrl = curTime;
        }
        else{ //previous temperature already out of set limits
            if ((curTime - ini_time_ctrl) > set_time) {
                systemStatus = systemInfo::TEMP_NOT_REACHED;
                cout << "Temperature has been out of the set limits too long" <<endl;
            }
        }
        tempStatus = tempInfo::TEMP_TOO_COLD;
        cout << "Temperature too cold" <<endl;
        HeatUp();
    }
    else if (currentTemp > maxTempSet){
        if (tempStatus == tempInfo::TEMP_OK) { //if previous temperature read had been ok, this is the beginning of a new temperature control
            ini_time_ctrl = curTime;
        }
        else{ //previous temperature already out of set limits
            if ((curTime - ini_time_ctrl) > set_time) {
                systemStatus = systemInfo::TEMP_NOT_REACHED;
                cout << "Temperature has been out of the set limits too long" <<endl;
            }
        }
        tempStatus = tempInfo::TEMP_TOO_HOT;
        cout << "Temperature too hot" <<endl;
        Cool();
    }
    else{
        tempStatus = tempInfo::TEMP_OK;
        cout << "Temperature is OK" <<endl;
    }

}
void TempControl::Cool(){ //activate cool mechanism
    cout << "Cooling" <<endl;
    //Activate real cooling mechanism
} 
void TempControl::HeatUp(){ //activate heat up mechanism
    cout << "Heating up" <<endl;
    //Activate real heating mechanism
} 
void TempControl::SetTime(unsigned int setTime){ //define set_time, especially if not defined in constructor 2 or changing its value on the fly
    set_time = setTime;
} 

