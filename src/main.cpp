#include <Arduino.h>
#include "Config.hpp"

#include "Network.hpp"
#include "Message.hpp"
#include "Plants.hpp"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */

void setup()
{
  /*TODO:
    - Include logic for listening to MQTT message as a setup possibility
    - Test Sensor Reading code
    - Test overall code
  */


  // put your setup code here, to run once:

  //load config
  Config::setup();
  //try to connect to network & mqtt

  #ifdef DEBUG_SENSOR
    Serial.begin(115200);
    sleep(1000);
  #else
    AsyncMqttClientInternals::OnMessageUserCallback messageHandler = Message::onMessage;
    Network::setup(messageHandler);
  #endif
}
void loop()
{
  #ifdef DEBUG_SENSOR
    Serial.println(Plants::read_sensor(0));
  #else
    Network::loop();
    // put your main code here, to run repeatedly:
    
    //read the plants
    Plants::progress_all();
    
    //put the esp into deep_sleep
    esp_sleep_enable_timer_wakeup(Config::sleep_seconds * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
    delay(1000);
  #endif
}