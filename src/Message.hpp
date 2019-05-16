#ifndef DOORBELL_MESSAGE_HPP
#define DOORBELL_MESSAGE_HPP

#include <AsyncMqttClient.h>
#include <ArduinoJson.h>
#include "Arduino.h"

#include "Config.hpp"

namespace Message {

    void onMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
        Serial.print("Got the Message:");
        Serial.println(payload);
        DynamicJsonBuffer jsonBuffer;

        JsonObject &control_message = jsonBuffer.parseObject(payload);
        String command = control_message["command"].as<String>();
        const char* messagePayload = control_message["payload"];

        Serial.print(F("Got the following command: "));
        Serial.println(command);
        Serial.print(F("Got the following payload: "));
        Serial.println(control_message["payload"].as<String>());

        if (command.equalsIgnoreCase("play")) {

        } else if (command.equalsIgnoreCase("selectRingFile")) {
            
        }
        else
        {
            Serial.print("Got some other command:");
            Serial.println(command);
        }

    };

}

#endif //DOORBELL_MESSAGE_HPP
