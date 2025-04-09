#ifndef AI_MODEL_H
#define AI_MODEL_H

#include <string>

class AI_Model
{
public:
    void addData(int humidity, int temperature);
    std::string makeDecision();
};

#endif // AI_MODEL_H