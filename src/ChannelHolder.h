#ifndef SMART_WATERING_CHANNELHOLDER_H
#define SMART_WATERING_CHANNELHOLDER_H

#include "Channel.h"

class ChannelHolder {
public:
    ChannelHolder(byte maxChannelCount) {
        this->channels = new Channel *[maxChannelCount];
    }

    void addChannel(Channel *channel) {
        this->channels[channelCount] = channel;
        channelCount++;
    }

    void startEnable() {
        currentChannel = 0;
        enableCurrent();
    }

    bool nextEnable() {
        disableCurrent();

        currentChannel++;
        if (currentChannel < channelCount) {
            enableCurrent();
            return true;
        }

        Serial.println("Finish all channels");
        return false;
    }

    Channel *current() const {
        return channels[currentChannel];
    }

private:

    byte channelCount = 0;
    byte currentChannel = 0;

    Channel **channels;

    void enableCurrent() {
        current()->enable();
        Serial.print("Enable channel [");
        Serial.print(currentChannel);
        Serial.print("] for [");
        Serial.print(current()->getEnabledMinutes());
        Serial.println("] minutes");
    }

    void disableCurrent() {
        current()->disable();
        Serial.print("Disable channel [");
        Serial.print(currentChannel);
        Serial.println("]");
    }
};


#endif
