#ifndef PLANTS_HPP
#define PLANTS_HPP
#include <Arduino.h>
#include "Config.hpp"
#include <driver/adc.h>
#include "Network.hpp"
#include "Message.hpp"



namespace Plants
{
    void read_single(int plant_number);
    bool check_watering_single(int plant_number);
    void water_single(int plant_number);
    int read_sensor(int pin);

    void progress_all()
    {
        for (int i = 0; i < Config::plant_number; i++)
            {
                read_single(i);
                if (check_watering_single(i))
                {
                    water_single(i);
                }
            }
    }

    void read_single(int plant_number)
    {
        //just a dummy, replace with actual reading method.
        int value = 0;
        value = read_sensor(Config::read_pin[plant_number]);
        Config::last_read[plant_number] = value;
        Network::send(Config::mqtt_value_topic, (char*)value);
        //check_watering_single(plant_number);
    }
    int read_sensor(int channel)
    {
        //we can only use ADC1, since ADC2 is used for WiFi
        /*
            ADC1_CHANNEL_0 = 0
            ADC1 channel 0 is GPIO36

            ADC1_CHANNEL_1
            ADC1 channel 1 is GPIO37

            ADC1_CHANNEL_2
            ADC1 channel 2 is GPIO38

            ADC1_CHANNEL_3
            ADC1 channel 3 is GPIO39

            ADC1_CHANNEL_4
            ADC1 channel 4 is GPIO32

            ADC1_CHANNEL_5
            ADC1 channel 5 is GPIO33

            ADC1_CHANNEL_6
            ADC1 channel 6 is GPIO34

            ADC1_CHANNEL_7
            ADC1 channel 7 is GPIO35
        */

        adc1_config_width(ADC_WIDTH_BIT_10);   //Range 0-1023 
        adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);  //ADC_ATTEN_DB_11 = 0-3,6V
        return adc1_get_raw( channel ); //Read analog
        //return analogRead(pin);
    }

    bool check_watering_single(int plant_number)
    {
        if (Config::last_read[plant_number] < Config::thresholds[plant_number])
        {
            return true;
            //water_single(plant_number);
        }
        else
        {
            return false;
        }
    }

    void water_single(int plant_number)
    {
        digitalWrite(Config::waterPin[plant_number],HIGH);
        sleep(5);
        digitalWrite(Config::waterPin[plant_number],LOW);
        Network::send("/Plants/Watered", Config::plant_names[plant_number]);
    }
}
#endif