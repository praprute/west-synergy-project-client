


// nrf24_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_NRF24 class. RH_NRF24 class does not provide for addressing or
// reliability, so you should only use RH_NRF24  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example nrf24_client
// Tested on Uno with Sparkfun NRF25L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <SPI.h>
#include <RH_NRF24.h>
#include <Wire.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

void setup()
{
  Serial.begin(9600);
  Wire.begin();

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

int sensor;

int us42(){
  Wire.beginTransmission(112);
  Wire.write(byte(81));
  Wire.endTransmission();
  delay(70);
  Wire.requestFrom(112, 2);
   if (2 <= Wire.available()) {
    int reading = Wire.read();
    reading = reading << 8;
    reading |= Wire.read();
//    Serial.print("sensorxxxx : ");
//    Serial.println(reading);
     
    return reading;
  }
 
}

int maSensor(){
  int count = 10;
  int sum = 0;
  for(int i ; i <= count ; i++){
    sum += us42();
  }

  int val = sum/count;
  if(val != 0){
    int sendVal = val;
    Serial.print("maVal : ");
    Serial.println(sendVal);

    sendVal = map(sendVal, 20, 300, 100, 0);
    return sendVal;
  }
}



void loop()
{
  String s_sensor =  String(maSensor());
   maSensor();
  
  if (nrf24.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      //NRF24::printBuffer("request: ", buf, len);
      //Serial.print("got request: ");
      
      //Serial.println((char*)buf);

      //char id = ((char)buf[1]);

      String id = char2String((char)buf[0]) + char2String((char)buf[1]);
      Serial.println(id);
      
      if (char2String((char)buf[0]) == "A" &&  char2String((char)buf[1]) == "1") {
        char sensor_char[s_sensor.length() + 1];
        s_sensor.toCharArray(sensor_char, s_sensor.length() + 1);
        nrf24.send(sensor_char, sizeof(sensor_char));
        nrf24.waitPacketSent();
        Serial.print("sensor : ");
        Serial.println(s_sensor);
        Serial.println("Yes I'am");

      } else {
         Serial.println("fail");
      }

      //String val = char2String((char)buf[4]) + char2String((char)buf[5]) + char2String((char)buf[6]);

      // Send a reply
      //uint8_t data[] = "And hello back to you";
      //String id = id_sensor;
      //nrf24.send(data, sizeof(data));
      //Serial.println("Sent a reply");
    }
    else
    {

    }
  }
}

String char2String(char val) {
  String buf;
  switch (val) {
    case '0': buf = "0"; break;
    case '1': buf = "1"; break;
    case '2': buf = "2"; break;
    case '3': buf = "3"; break;
    case '4': buf = "4"; break;
    case '5': buf = "5"; break;
    case '6': buf = "6"; break;
    case '7': buf = "7"; break;
    case '8': buf = "8"; break;
    case '9': buf = "9"; break;
    case 'A': buf = "A"; break;
    case 'B': buf = "B"; break;
    case 'C': buf = "C"; break;
  }

  return buf;
}
