
//int readingCm = 0;
//int getDistance( int address)
//{
//
//  Wire.beginTransmission(address);
//  Wire.write(byte(0x00));
//  Wire.write(byte(0x51));
//  Wire.endTransmission();
//
//  delay(70);
//  Wire.beginTransmission(address);
//  Wire.write(byte(0x02));
//  Wire.endTransmission();
//
//  Wire.requestFrom(112, 2);
//  if (2 <= Wire.available()) {
//    readCm = Wire.read();
//    readCm = readCm << 8;
//    readCm |= Wire.read();
//    return readCm;
//  }
//  
//
//}
