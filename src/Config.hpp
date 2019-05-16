#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <Preferences.h>

Preferences settings;

namespace Config
{
    String mqtt_value_topic;
    const int plant_number = 4;
    int thresholds[plant_number];
    String plant_names[plant_number];
    
void save()
{
    settings.putString("mqtt_topic",mqtt_value_topic);
    for (int i = 0; i < plant_number; i++)
    {
        settings.putInt(("thresholds" + (String)i).c_str(), thresholds[i]);
        settings.putString(("plant_names" + (String)i).c_str(), plant_names[i] );
    }
}

void setup()
{
    settings.begin("plants", false);
    mqtt_value_topic = settings.getString("mqtt_topic","/Plants/values");
    for (int i = 0; i < plant_number; i++)
    {
       thresholds[i] = settings.getInt(("thresholds" + (String)i).c_str(), 20);
       plant_names[i] = settings.getString(("plant_names" + (String)i).c_str(), "Plant" + (String)i );
    }
}

}; // namespace Config

#endif //Config