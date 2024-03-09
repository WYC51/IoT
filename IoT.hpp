#ifndef _IOT_HPP
#define _IOT_HPP

#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 7 
#define DHTTYPE DHT11
#define serialCommunicationSpeed 9600
#define DEBUG true

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial esp8266(10,11);

String API = "{API_KEY}"; // get this key from thingspeak.com

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";                                             
    esp8266.print(command);                                       
    long int time = millis();                                      
    while( (time+timeout) > millis())                                 
    {      
      while(esp8266.available())                                      
      {
        char c = esp8266.read();                                     
        response+=c;                                                  
      }  
    }    
    if(debug)                                                        
    {
      Serial.print("\n");
      Serial.print(response);
    }    
    return response;                                                  
}


void InitWifiModule()
{
  sendData("AT+RST\r\n", 2000, DEBUG);
  delay (1500);

  sendData("AT+CWJAP=\"{WIFI_NAME}\",\"{WIFI_PWD}\"\r\n", 2000, DEBUG);
  delay (3000);
  
  sendData("AT+CIFSR\r\n", 1500, DEBUG);                                             
  delay (3000);

  sendData("AT+CIPMUX=0\r\n", 1500, DEBUG);  
  delay (3000);
  
  sendData("AT+CWMODE=1\r\n", 1500, DEBUG);
  delay (3000);
}

void sendSignal(double i, double j){

  sendData("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", 3000, DEBUG);
  delay (6000);

  sendData("AT+CIPSEND=70\r\n", 1500, DEBUG);  
  delay (3000);

  String str="GET /update?api_key="+ API +"&field1=" + String(i) + "&field2=" + String(j) + "\r\n";
  sendData(str, 3000, DEBUG);
  delay (6000);

  sendData("AT+CIPCLOSE\r\n", 1500, DEBUG);
  delay (3000);
  }

#endif