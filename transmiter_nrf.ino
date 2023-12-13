#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;
const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10); //  CN and CSN  pins of nrf
struct MyData {
  byte p;
  byte t;
};
MyData data;
void setup()
{
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}
void loop()
{
  data.p = bmp.readPressure();
  data.t = bmp.readTemperature();
  if (isnan(data.p) || isnan(data.t)){
    Serial.println(F("Failed to read from BMP180 sensor!"));
    return;
  }
  Serial.print("Pressure: ");
  Serial.print(data.p);
  Serial.print("Temperature: ");
  Serial.print(data.t); 
  radio.write(&data, sizeof(MyData));
}

    
