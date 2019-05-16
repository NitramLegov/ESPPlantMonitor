#include <Arduino.h>
#include "Config.hpp"

#include "Network.hpp"
#include "Message.hpp"

void setup()
{
  // put your setup code here, to run once:

  //load config
  Config::setup();
  //try to connect to network & mqtt

}
void loop()
{
  // put your main code here, to run repeatedly:
  
  //read the plants
  //try to send 

}