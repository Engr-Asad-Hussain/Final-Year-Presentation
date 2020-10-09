/* CE   : 9
   CSN  : 10
   MOSI : 11
   MISO : 12
   SCK  : 13
*/

/*-----------------------------------------------MOTOR DRIVER-----------------*/

// INITIALIZATION OF LEFT MOTOR
#define RPWM_left 7         // define pin 7 for RPWM pin (output)
#define R_EN_left 200       // define Vcc for R_EN pin (input)
#define R_IS_left 5         // define pin 5 for R_IS pin (output)
#define LPWM_left 4         // define pin 4 for LPWM pin (output)
#define L_EN_left 200       // define vcc for L_EN pin (input)
#define L_IS_left 6         // define pin 6 for L_IS pin (output)
#define debug_left 1        // change to 0 to hide serial monitor debugging infornmation or set to 1 to view

#define RPWM_right 14       // define pin 14 for RPWM pin (output) active high
#define R_EN_right 200      // define vcc for R_EN pin (input) high enable, low close
#define R_IS_right 16       // define pin 16 for R_IS pin (output)
#define LPWM_right 17       // define pin 17 for LPWM pin (output) active high
#define L_EN_right 200      // define vcc for L_EN pin (input) high enable, low close
#define L_IS_right 15       // define pin 15 for L_IS pin (output)
#define debug_right 1

#define CW 1                // do not change
#define CCW 0               // do not change

#include <RobojaxBTS7960.h>
RobojaxBTS7960 motor_left(R_EN_left, RPWM_left, R_IS_left, L_EN_left, LPWM_left, L_IS_left, debug_left);
RobojaxBTS7960 motor_right(R_EN_right, RPWM_right, R_IS_right, L_EN_right, LPWM_right, L_IS_right, debug_right);

#include <SPI.h>`
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);                    // CE, CSN
const byte address[6] = "00001";
int receivedData;

struct Received_data {
  int ch1;
  int ch2;
  int ch3;
};

Received_data received_data;

int ch1_value = 0;
int ch2_value = 0;
int ch3_value = 0;

void reset_the_Data() 
{
  received_data.ch1 = 512;
  received_data.ch2 = 512;
  received_data.ch3 = 0;
}

int relay_en_left = 3;
int relay_en_right = 2;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); // 00001
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  reset_the_Data();

  motor_left.begin();
  motor_right.begin();

  pinMode(relay_en_left, OUTPUT);
  pinMode(relay_en_right, OUTPUT);
  digitalWrite(relay_en_left, HIGH);
  digitalWrite(relay_en_right, HIGH);
}


unsigned long lastRecvTime = 0;

void receive_the_data()  {
  while ( radio.available() ) {
  radio.read(&received_data, sizeof(Received_data));
  lastRecvTime = millis();
  }
}

void loop() {
  receive_the_data();
  
  Serial.print("xAxis : ");
  Serial.print(int(received_data.ch1));
  Serial.print("\tyAxis : ");
  Serial.print(int(received_data.ch2));
  Serial.print("\tbutton : ");
  Serial.print(int(received_data.ch3));
  Serial.println();

  int x = int(received_data.ch1);
  int y = int(received_data.ch2);
  int z = int(received_data.ch3);


  if ( z == HIGH)  {
    digitalWrite(relay_en_right, LOW);
    digitalWrite(relay_en_left, LOW);
    if ( x >= 800)  {
      motor_right.rotate(100,CW);
      motor_left.rotate(100,CCW);
    }
    else if ( x <= 300 )  {
      motor_right.rotate(100,CCW);
      motor_left.rotate(100, CW);
    }
    else if ( y >= 800 )  {                 // Forward
      motor_right.rotate(80, CW);
      motor_left.rotate(80, CW);
    }
    else if ( y <= 300 )  {                 // Reverse
      motor_right.rotate(100, CCW);
      motor_left.rotate(100, CCW);
    }
    else {
      motor_right.rotate(0, CCW);
      motor_left.rotate(0, CCW);
    }  
  }
  else  {
    digitalWrite(relay_en_left, HIGH);
    digitalWrite(relay_en_right, HIGH);
  }
}
