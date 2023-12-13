#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h> 
const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);
struct MyData {
  byte p; 
  byte t;
};
MyData data;
void setup()
{
  Serial.begin(9600); 
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();
  //lcd.println("Receiver ");
}
void recvData()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(MyData));
    }
}
void loop()
{
  recvData();
  Serial.print("Pressure: ");
  Serial.print(data.p);
  Serial.print("Temperature: ");
  Serial.print(data.t); 
  Serial.print("\n");
}
