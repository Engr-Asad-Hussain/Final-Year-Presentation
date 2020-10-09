/* CE   : 9
   CSN  : 10
   MOSI : 11
   MISO : 12
   SCK  : 13
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define xAxis_joystic A0
#define yAxis_joystic A1
#define button 2  

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

struct Data_to_be_sent {
  int ch1;
  int ch2;
  int ch3;
};

//Create a variable with the structure above and name it sent_data
Data_to_be_sent sent_data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address); // 00001
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  pinMode(button, INPUT);
  //Reset each channel value
  sent_data.ch1 = 512;
  sent_data.ch2 = 512;
  sent_data.ch3 = 0;
}

void loop() {
  sent_data.ch1 = int(analogRead(xAxis_joystic));
  sent_data.ch2 = int(analogRead(yAxis_joystic));
  sent_data.ch3 = digitalRead(button);
  radio.write(&sent_data, sizeof(sent_data));
}
