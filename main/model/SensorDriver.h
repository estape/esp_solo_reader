#ifndef SENSORDRIVER_H
#define SENSORDRIVER_H

#include <iostream>
#include <string.h>

class SensorDriver
{
public:
    bool CheckRegex(std::string moistureValue);
    int GetMoistureLevel(int moistureValue);
};

#endif // SENSOR_DRIVER_H