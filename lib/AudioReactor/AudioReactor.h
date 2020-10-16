#pragma once

#include <Arduino.h>

#define MAX_ANALOG 1023
#define MAX_OUT 255
#define BASELINE 255
#define MIDDLE_VAL 535
#define NUMBER_SAMPLES 64
#define AVERAGED_OVER 20
#define HOMING_FACTOR 500
#define ZERO_THRESHOLD 0

class AudioReactor
{
private:
    int m_NumPorts;
    uint8_t *m_InPorts,
            *m_OutPorts;
    
    float *m_RunningAverages,
          *m_MaxSounds,
          *m_SumsOfSquares;

public:
    AudioReactor(uint8_t inPorts [], uint8_t outPorts [], int numPorts);
    ~AudioReactor();

    void start();
    float clamp(float value, float max, float min);
    void tick();
    void getMaxSound(int i);
    int getReaction(int i);
};