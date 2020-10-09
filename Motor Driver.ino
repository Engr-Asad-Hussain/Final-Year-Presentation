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
}

void loop() {
  motor_left.rotate(100,CCW);// run motor with 100% speed in CW direction
  motor_right.rotate(100,CW);
}
