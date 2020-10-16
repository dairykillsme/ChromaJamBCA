#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

enum Status {
    OKAY,
    ERR_SERIAL_NOT_LISTENING,
    ERR_INVALID_DFPLAYER,
};

class AudioController
{
private:
    SoftwareSerial m_SerialPort = SoftwareSerial(10, 11);
    DFRobotDFPlayerMini m_AudioPlayer;

public:
    AudioController(uint8_t rx, uint8_t tx);
    ~AudioController();
    Status init();
    Status playFirst();
    Status startLoop();
};