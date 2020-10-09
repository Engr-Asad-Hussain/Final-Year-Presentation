#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>  
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);                     // RX, TX

#define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

char auth[] = "Nq9hq02rUGX_xXwcjnarStHH8IZxxxxx";
char ssid[] = "AndroidAP";
char pass[] = "xxxxxxxxx";

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


void setup() {
  motor_left.begin();
  motor_right.begin();

  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
}


int VirtualPin_5;               // Forward Virtual Pin of GUI Blynk Application
BLYNK_WRITE(V5)
{   
  VirtualPin_5 = param.asInt(); // Get value as integer
}

int VirtualPin_10;              // Reverse Virtual Pin of GUI Blynk Application
BLYNK_WRITE(V10)
{   
  VirtualPin_10 = param.asInt();
}

int VirtualPin_15;               // Left Virtual Pin of GUI Blynk Application
BLYNK_WRITE(V15)
{   
  VirtualPin_15 = param.asInt();
}

int VirtualPin_20;                // Right Virtual Pin of GUI Blynk Application
BLYNK_WRITE(V20)
{   
  VirtualPin_20 = param.asInt();
}


void loop() { 

  if (VirtualPin_5 == 1)  {               //Forward
    motor_right.rotate(80, CCW);
    motor_left.rotate(80, CCW);
  }
  else if (VirtualPin_10 == 1)  {         //Reverse
    motor_right.rotate(80, CW);
    motor_left.rotate(80, CW);
  }
  else if (VirtualPin_15 == 1)  {         //Right
    motor_right.rotate(80, CW);
    motor_left.rotate(80, CCW);
  }
  else if (VirtualPin_20 == 1)  {         //Left
    motor_right.rotate(80, CCW);
    motor_left.rotate(80, CW);
  }
  else  {
    motor_right.rotate(0, CCW);
    motor_left.rotate(0, CCW);
  }
  Blynk.run();
  
}
