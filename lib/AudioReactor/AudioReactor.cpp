#include "AudioReactor.h"

void(*resetFunc) (void) = 0; //declare reset function @ address 0

AudioReactor::AudioReactor(uint8_t inPorts [], uint8_t outPorts [], int numPorts)
{
    m_InPorts = inPorts;
    m_OutPorts = outPorts;
    m_NumPorts = numPorts;
    m_RunningAverages = new long[m_NumPorts];
    m_MaxSounds = new long[m_NumPorts];
    m_SumsOfSquares = new long[m_NumPorts];
    m_RecalCounters = new long[m_NumPorts];
}

AudioReactor::~AudioReactor()
{
    delete [] m_RunningAverages;
    delete [] m_MaxSounds;
    delete [] m_SumsOfSquares;
    delete [] m_RecalCounters;
}

void AudioReactor::start() {
    for (int i = 0; i < m_NumPorts; i++)
    {
        pinMode(m_InPorts[i], INPUT);
        pinMode(m_OutPorts[i], OUTPUT);
        m_RunningAverages[i] = 0;
        m_MaxSounds[i] = 0;
        m_RecalCounters[i] = 0;
        m_SumsOfSquares[i] = 0;
    }
}

long AudioReactor::clamp(int value, int mmax, int mmin) {
    return constrain(map(value, mmin, mmax, 0, MAX_OUT), 0, MAX_OUT);
}

void AudioReactor::tick() {
    for (int j = 0; j < m_NumPorts; j++) {
        m_SumsOfSquares[j] = 0; //Reset Sum of Squares to 0
        // Collect samples for each channel
        for (int i = 0; i < NUMBER_SAMPLES; i++) {
            long sample = analogRead(m_InPorts[j]);
            // Reset safety for clipping audio (hopefully won't trigger)
            if (sample == 1023 || sample == 0) {
                resetFunc();
            }
            long signal = sample - MIDDLE_VAL;
            signal *= signal;
            m_SumsOfSquares[j] += signal;
        }
    }
    // Add samples to running average & output to LEDs
    for (int i = 0; i < m_NumPorts; i++) {
        long averageReading = m_SumsOfSquares[i] / NUMBER_SAMPLES;
        m_RunningAverages[i] = (((AVERAGED_OVER - 1) * m_RunningAverages[i]) + averageReading) / AVERAGED_OVER; // Calculate Running Averages
        getMaxSound(i);
        analogWrite(m_OutPorts[i], getReaction(i));
    }
}

void AudioReactor::getMaxSound(int i) {
    if (m_RunningAverages[i] > m_MaxSounds[i]) {
		m_MaxSounds[i] = m_RunningAverages[i];
		m_RecalCounters[i] = 0;
	} else {
		m_MaxSounds[i] -= (m_MaxSounds[i] - m_RunningAverages[i]) / HOMING_FACTOR;
		if (m_MaxSounds[i] < BASELINE) {
			m_MaxSounds[i] = BASELINE;
		}
	}
	if (m_RunningAverages[i] < 5) {
		m_RecalCounters[i] += 1;
		if (m_RecalCounters[i] > RECAL_TIME) {
			m_MaxSounds[i] = BASELINE;
			m_RecalCounters[i] = 0;
		}
	}
}

int AudioReactor::getReaction(int i) {
    return clamp(m_RunningAverages[i], m_MaxSounds[i], 0);
}