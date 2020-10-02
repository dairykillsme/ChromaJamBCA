#include "AudioController.h"

AudioController::AudioController(uint8_t rx, uint8_t tx) {
    m_SerialPort = SoftwareSerial(rx, tx);
}

AudioController::~AudioController() {
    m_SerialPort.end();
}

Status AudioController::init() {
    m_SerialPort.begin(9600);

    m_SerialPort.listen();
    if (!m_AudioPlayer.begin(m_SerialPort)) {
        return ERR_INVALID_DFPLAYER;
    }

    m_AudioPlayer.stop();
    m_AudioPlayer.volume(30); // This will have to be experimentally derived below clipping level
    m_AudioPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
    
    if (!m_SerialPort.stopListening()) {
        return ERR_SERIAL_NOT_LISTENING;
    }

    return OKAY;
}

Status AudioController::playFirst() {
    m_SerialPort.listen();
    m_AudioPlayer.play();
    if (!m_SerialPort.stopListening()) {
        return ERR_SERIAL_NOT_LISTENING;
    }
    return OKAY;
}