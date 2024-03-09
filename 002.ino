#include "IoT.hpp"

void setup()

{
  Serial.begin(serialCommunicationSpeed);           
  esp8266.begin(serialCommunicationSpeed);     
  InitWifiModule();
  dht.begin();
                                
}

void loop()                                                         
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  sendSignal(h, t);

  delay(60000);
}
