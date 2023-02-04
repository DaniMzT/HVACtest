#include "../tempControl/include/tempControl.h"
#include "gtest/gtest.h"

/*objects and initializations*/
const int TEMP_SENSOR_SENSITIVITY = 1; //deg/V. I'm working in V instead of mV for the sake of simplicity
const int TEMP_SENSOR_OFFSET = 1;
const int TEMP_SENSOR_MIN_V = 0; //V
const int TEMP_SENSOR_MAX_V = 24; //V

const int TEMP_MIN = 20; //deg in Celsius
const int TEMP_MAX = 22;
const int TEMP_TIME_ALLOWED = 15; 
int curRaw_V = 1; //current data sensor (in V)
unsigned int timeElapsed = 0;

//object for temperature sensor
Sensor tSensor(TEMP_SENSOR_SENSITIVITY, TEMP_SENSOR_MIN_V, TEMP_SENSOR_MAX_V, TEMP_SENSOR_OFFSET);
//object for temperature control
TempControl tControl(tSensor, TEMP_MIN, TEMP_MAX,TEMP_TIME_ALLOWED);

/*Test suite SystemOKTest: system and temperature ok */
//Test case: system ok, temperature ok
TEST(SystemOKTest, EverythingOK){
    curRaw_V = 1+(TEMP_MIN/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET;  //between TEMP_MIN and T_MAX
    timeElapsed++; //1
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::SYSTEM_OK);
    curRaw_V = (TEMP_MIN/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET; //TEMP_MIN
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::SYSTEM_OK);
    curRaw_V = (TEMP_MAX/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET; //TEMP_MAX
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::SYSTEM_OK);
}

//Test case: system ok, time exceeding set time (it should not affect)
TEST(SystemOKTest, LongTime){
    curRaw_V = 1+(TEMP_MIN/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET;
    timeElapsed++; //2
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::SYSTEM_OK);
}

/*Test suite TemperatureIssues: temperature out of limits, sensor working properly */
//Test cases: system ok, temperature too cold
TEST(TemperatureIssues, TooCold){
    timeElapsed++;//3
    curRaw_V = (TEMP_MIN/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET - 1; 
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(tempStatus, tempInfo::TEMP_TOO_COLD);
}

//Test case: system ok, temperature too cold and too long out of limits
TEST(TemperatureIssues, TooColdTooLong){
    timeElapsed += (TEMP_TIME_ALLOWED+1);
    curRaw_V = (TEMP_MIN/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET - 1;
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::TEMP_NOT_REACHED);
    ASSERT_EQ(tempStatus, tempInfo::TEMP_TOO_COLD);
}

//Test case: temperature back to normal, all ok
TEST(TemperatureIssues, TempOKafterCold){
    curRaw_V = (TEMP_MAX/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET; //TEMP_MAX
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::SYSTEM_OK);
    ASSERT_EQ(tempStatus, tempInfo::TEMP_OK);
}

//Test case: system ok, temperature too hot
TEST(TemperatureIssues, TooHot){
    curRaw_V = (TEMP_MAX/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET +1; 
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(tempStatus, tempInfo::TEMP_TOO_HOT);
}

//Test cases: system ok, temperature too hot and too long out of limits
TEST(TemperatureIssues, TooHotTooLong){
    timeElapsed += (TEMP_TIME_ALLOWED+1); //elapsed time reset in last ok temperature
    curRaw_V = (TEMP_MAX/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET +1; 
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::TEMP_NOT_REACHED);
    ASSERT_EQ(tempStatus, tempInfo::TEMP_TOO_HOT);
}

//Test case: temperature back to normal, all ok
TEST(TemperatureIssues, TempOKafterHot){
    curRaw_V = (TEMP_MAX/TEMP_SENSOR_SENSITIVITY)-TEMP_SENSOR_OFFSET; //TEMP_MAX
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::SYSTEM_OK);
    ASSERT_EQ(tempStatus, tempInfo::TEMP_OK);
}


/*Test suite SystemIssues: sensor not working properly */
//Test case: system under lower limit
TEST(SystemIssues, SensorUnderLimit){
    curRaw_V = TEMP_SENSOR_MIN_V - 1;
    timeElapsed = TEMP_TIME_ALLOWED -1;
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::ERROR_UNDER_MIN);
}

//Test case: system above higher limit
TEST(SystemIssues, SensorAboveLimit){
    curRaw_V = TEMP_SENSOR_MAX_V + 1;
    timeElapsed = TEMP_TIME_ALLOWED -1;
    tControl.controlTemp(curRaw_V, timeElapsed);
    ASSERT_EQ(systemStatus, systemInfo::ERROR_OVER_MAX);    
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


