/* CE   : 9
   CSN  : 10
   MOSI : 11
   MISO : 12
   SCK  : 13
*/

#include <SPI.h>`
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);                  // CE, CSN
const byte address[6] = "00001";
int receivedData;

struct Received_data {
  int ch1;
  int ch2;
};

Received_data received_data;

int ch1_value = 0;
int ch2_value = 0;

void reset_the_Data() 
{
  // 'safe' values to use when NO radio input is detected
  received_data.ch1 = 512;
  received_data.ch2 = 512;
}


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); // 00001
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  //We reset the received values
  reset_the_Data();
}

unsigned long lastRecvTime = 0;

//We create the function that will read the data each certain time
void receive_the_data()  {
  while ( radio.available() ) {
  radio.read(&received_data, sizeof(Received_data));
  lastRecvTime = millis();
  }
}

void loop()  {
  receive_the_data();

  //This small if will reset the data if signal is lost for 1 sec.
  unsigned long now = millis();
//  if ( now - lastRecvTime > 1000 ) {
//    // signal lost?
//    reset_the_Data();
//    //Go up and change the initial values if you want depending on your aplications.
//  }
  Serial.print("xAxis : ");
  Serial.print(int(received_data.ch1));
  Serial.print("\tyAxis : ");
  Serial.print(int(received_data.ch2));
  Serial.println();
}
