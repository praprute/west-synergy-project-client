#include <ArduinoJson.h>

// nrf24_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_NRF24 class. RH_NRF24 class does not provide for addressing or
// reliability, so you should only use RH_NRF24 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example nrf24_server.
// Tested on Uno with Sparkfun NRF25L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <SPI.h>
#include <RH_NRF24.h>


// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

String id_sensor ;
float  sensor;
unsigned long pm = 0;
unsigned long interval = 5000;


void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
}


void loop()
{
//  unsigned long cm = millis();
//  if(cm - pm >= 5000){
//    pm = cm;
//    id_sensor = "A1";
//  }

 if(Serial.available() != ""){
    id_sensor = Serial.readString();
 }
  
  //Serial.println("Sending to node");
  // Send a message to nrf24_server

  //StaticJsonDocument<200> doc;
  //doc["id"] = id_sensor;
  //doc["sensor"] = sensor;

  //   float battVoltageReading;
  //  String batt = String(battVoltageReading,2);
  //  uint8_t data[batt.length()];
  //  for(int i=0;i<batt.length();i++){
  //    data=batt.charAt(i);
  //  }


  //  String test = "test";
  //  char testChar[50];
  //  test.toCharArray(testChar, 50);
  //  nrf24.send(testChar, sizeof(testChar));


  //   float test = 1000;
  //   String x = String(test);
  //   char stringValue[100];
  //   char A = 'A';
  //   x +=
  
  //   itoa(x, stringValue, 10);//convert integer to ASCII string, number base 10
  
  //String id = "A1"; ---------------------
  
  char tt_char[id_sensor.length()+1];

  id_sensor.toCharArray(tt_char, id_sensor.length()+1);
  nrf24.send(tt_char, sizeof(tt_char));  //use strlen() to determine C-string length


  //  uint8_t data[] = {"{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}"};
  //  nrf24.send(data, sizeof(data));

  nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  

  if (nrf24.waitAvailableTimeout(500))
  {
    if (nrf24.recv(buf, &len))
    {
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    //Serial.println("No reply, is nrf24_server running?");
  }
  delay(400);
}
