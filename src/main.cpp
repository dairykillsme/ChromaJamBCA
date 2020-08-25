#include "Arduino.h"
#include <AudioController.h>
#include <RadiantMobo.h>
#include <AudioReactor.h>

AudioController audioControllerCh1(CH1_RX_PIN, CH1_TX_PIN),
                audioControllerCh2(CH2_RX_PIN, CH2_TX_PIN),
                audioControllerCh3(CH3_RX_PIN, CH3_TX_PIN);

uint8_t audioInputPorts[] = {CH1_IN, CH2_IN, CH3_IN};
uint8_t audioOutputPorts[] = {CH1_PWM, CH2_PWM, CH3_PWM};
AudioReactor reactor = AudioReactor(audioInputPorts, audioOutputPorts, 3);

void initAudioControllers();
void playAudioControllers();

void setup()
{
    Serial.begin(115200);
    initAudioControllers();
    playAudioControllers();
    reactor.start();
}

void loop()
{
    reactor.tick();
}

void initAudioControllers() {
    // Channel 1
    auto err = audioControllerCh1.init();
    if (!err) {
        Serial.println("Channel 1 initialized");
    } else {
        Serial.print("Channel 1 failed to init with error code ");
        Serial.println(err);
    }
    //Channel 2
    err = audioControllerCh2.init();
    if (!err) {
        Serial.println("Channel 2 initialized");
    } else {
        Serial.print("Channel 2 failed to init with error code ");
        Serial.println(err);
    }
    //Channel 3
    err = audioControllerCh3.init();
    if (!err) {
        Serial.println("Channel 3 initialized");
    } else {
        Serial.print("Channel 3 failed to init with error code ");
        Serial.println(err);
    }
}

void playAudioControllers() {
    //Channel 1
    auto err = audioControllerCh1.playFirst();
    if (!err) {
        Serial.println("Channel 1 Playing");
    } else {
        Serial.print("Channel 1 failed to play song with error code " + err);
        Serial.println(err);
    }
    //Channel 2
    err = audioControllerCh2.playFirst();
    if (!err) {
        Serial.println("Channel 2 Playing");
    } else {
        Serial.print("Channel 2 failed to play song with error code " + err);
        Serial.println(err);
    }
    //Channel 3
    err = audioControllerCh3.playFirst();
    if (!err) {
        Serial.println("Channel 3 Playing");
    } else {
        Serial.print("Channel 3 failed to play song with error code " + err);
        Serial.println(err);
    }
}