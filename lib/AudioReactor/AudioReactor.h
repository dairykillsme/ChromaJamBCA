#pragma once

#include <Arduino.h>

#define MAX_ANALOG 1023
#define MAX_OUT 255
#define MIDDLE_VAL 512
#define NUMBER_SAMPLES 128
#define AVERAGED_OVER 25
#define RECAL_TIME 100
#define HOMING_FACTOR 500

class AudioReactor
{
private:
    int m_NumPorts;
    uint8_t *m_InPorts,
            *m_OutPorts;
    
    long *m_RunningAverages,
          *m_MaxSounds,
          *m_SumsOfSquares,
          *m_RecalCounters;

public:
    AudioReactor(uint8_t inPorts [], uint8_t outPorts [], int numPorts);
    ~AudioReactor();

    void start();
    long clamp(int value, int max, int min);
    void tick();
    void getMaxSound(int i);
    int getReaction(int i);
};