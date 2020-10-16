#include "AudioReactor.h"

AudioReactor::AudioReactor(uint8_t inPorts [], uint8_t outPorts [], int numPorts)
{
    m_InPorts = inPorts;
    m_OutPorts = outPorts;
    m_NumPorts = numPorts;
    m_RunningAverages = new float[m_NumPorts];
    m_MaxSounds = new float[m_NumPorts];
    m_SumsOfSquares = new float[m_NumPorts];
}

AudioReactor::~AudioReactor()
{
    delete [] m_RunningAverages;
    delete [] m_MaxSounds;
    delete [] m_SumsOfSquares;
}

void AudioReactor::start() {
    for (int i = 0; i < m_NumPorts; i++)
    {
        pinMode(m_InPorts[i], INPUT);
        pinMode(m_OutPorts[i], OUTPUT);
        m_RunningAverages[i] = 0;
        m_MaxSounds[i] = BASELINE;
        m_SumsOfSquares[i] = 0;
    }
}

float AudioReactor::clamp(float value, float mmax, float mmin) {
    return constrain(map(value, mmin, mmax, 0, MAX_OUT), 0, MAX_OUT);
}

void AudioReactor::tick() {
    for (int j = 0; j < m_NumPorts; j++) {
        m_SumsOfSquares[j] = 0; //Reset Sum of Squares to 0
        // Collect samples for each channel
        for (int i = 0; i < NUMBER_SAMPLES; i++) {
            float sample = analogRead(m_InPorts[j]);
            float signal = sample - MIDDLE_VAL;
            signal *= signal;
            m_SumsOfSquares[j] += signal;
        }
    }
    // Add samples to running average & output to LEDs
    for (int i = 0; i < m_NumPorts; i++) {
        float averageReading = m_SumsOfSquares[i] / NUMBER_SAMPLES;
        if (i == 2)
        {
            Serial.print(averageReading);
        }
        
        m_RunningAverages[i] = (((AVERAGED_OVER - 1) * m_RunningAverages[i]) + averageReading) / AVERAGED_OVER; // Calculate Running Averages
        getMaxSound(i);
        analogWrite(m_OutPorts[i], getReaction(i));
    }
    Serial.print(" ");
    Serial.print(m_RunningAverages[2]);
    Serial.print(" ");
    Serial.println(m_MaxSounds[2]);
}

void AudioReactor::getMaxSound(int i) {
    if (m_RunningAverages[i] > m_MaxSounds[i]) {
		m_MaxSounds[i] = m_RunningAverages[i];
	} else {
		m_MaxSounds[i] -= (m_MaxSounds[i] - m_RunningAverages[i]) / HOMING_FACTOR;
		if (m_MaxSounds[i] < BASELINE) {
			m_MaxSounds[i] = BASELINE;
		}
	}
}

int AudioReactor::getReaction(int i) {
    float reaction = clamp(m_RunningAverages[i], m_MaxSounds[i], 0);
    if (reaction < ZERO_THRESHOLD) {
        return 0;
    } else {
        return reaction;
    }
}