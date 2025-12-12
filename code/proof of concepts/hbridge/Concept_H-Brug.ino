/* This is a simple sketch to allow you to get up and running quickly
 *  with a DRV8833 breakout board. To support my work check out my
 *  YouTube channel; https://www.youtube.com/SimpleElectronics or buy
 *  your DRV8833 using my affiliate link here: 
 *  https://s.click.aliexpress.com/e/_DEvY5zz
 */

// Setting up pins for the DRV8833 board to use as inputs. 
// (11, 10, 9, 6, 5 and 3 are PWM capable on UNO - using a PWM capable pin will
// allow us to control motor speed)

// Setting the 4 "signal" pins for the DRV8833 - sig1 and sig2 control one motor,
// sig3 and sig4 control another.
const int sig1 = 10;
const int sig2 = 9;
const int sig3 = 6;
const int sig4 = 5;


void setup() {
// Setting pinMode to outputs to communicate with the DRV8833 board

pinMode(sig1, OUTPUT);
pinMode(sig2, OUTPUT);
pinMode(sig3, OUTPUT);
pinMode(sig4, OUTPUT);

// Ensure that the output pins are set to a known state (LOW) so the motors don't start on their own
digitalWrite(sig1, LOW);
digitalWrite(sig2, LOW);
digitalWrite(sig3, LOW);
digitalWrite(sig4, LOW);

}

void loop() {
  
/*  This loop just steps between the different ways we can control the motors connected
 *  to the DRV8833 board for a second. Spin motor A counter-clockwise, then clockwise. 
 *  Spin motor B counter-clockwise, then clockwise. Then it will repeat the process at 
 *  half speed. Between the steps it will stop all the motors for a second.
 *  If your motor spins the opposite direction from what you expected, just reverse the
 *  polarity of your motor.
 *  Go look at the associated function below the loop to learn more about how the control
 *  works.
 */

motorA_CCW();
delay(1000);

stopAllMotors();
delay(1000);

motorA_CW();
delay(1000);

stopAllMotors();
delay(1000);

motorB_CCW();
delay(1000);

stopAllMotors();
delay(1000);

motorB_CW();
delay(1000);

stopAllMotors();
delay(1000);

motorA_CCW_Half();
delay(1000);

stopAllMotors();
delay(1000);

motorA_CW_Half();
delay(1000);

stopAllMotors();
delay(1000);

motorB_CCW_Half();
delay(1000);

stopAllMotors();
delay(1000);

motorB_CW_Half();
delay(1000);

stopAllMotors();
delay(1000);

}

void stopAllMotors() {

  // Setting the signals all to HIGH or all to LOW will stop them from turning
  digitalWrite(sig1, LOW);
  digitalWrite(sig2, LOW);
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, LOW);
}

void motorA_CCW() {
  
  // Having one signal high and another low will cause the motor to turn at full speed
  // Changing which one is HIGH will change the spin direction
  digitalWrite(sig1, HIGH);
  digitalWrite(sig2, LOW);
}

void motorA_CW() {

  // Having one signal high and another low will cause the motor to turn at full speed
  // Changing which one is HIGH will change the spin direction
  digitalWrite(sig1, LOW);
  digitalWrite(sig2, HIGH);
}

void motorA_CCW_Half() {

  // We perform an analogWrite on whichever signal is HIGH to control the speed of the
  // motor, a value of 0 is OFF and 255 is max speed, equivalent of writing HIGH
  // changing which one is bring driven HIGH changes the direction of spin
  analogWrite(sig1, 127);
  digitalWrite(sig2, LOW);
}

void motorA_CW_Half() {

  // We perform an analogWrite on whichever signal is HIGH to control the speed of the
  // motor, a value of 0 is OFF and 255 is max speed, equivalent of writing HIGH
  // changing which one is bring driven HIGH changes the direction of spin
  digitalWrite(sig1, LOW);
  analogWrite(sig2, 127);
}

void motorB_CCW() {

  // Having one signal high and another low will cause the motor to turn at full speed
  // Changing which one is HIGH will change the spin direction
  digitalWrite(sig3, HIGH);
  digitalWrite(sig4, LOW);
}

void motorB_CW() {

  // Having one signal high and another low will cause the motor to turn at full speed
  // Changing which one is HIGH will change the spin direction
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, HIGH);
}

void motorB_CCW_Half() {

  // We perform an analogWrite on whichever signal is HIGH to control the speed of the
  // motor, a value of 0 is OFF and 255 is max speed, equivalent of writing HIGH
  // changing which one is bring driven HIGH changes the direction of spin
  analogWrite(sig3, 127);
  digitalWrite(sig4, LOW);
}

void motorB_CW_Half() {

  // We perform an analogWrite on whichever signal is HIGH to control the speed of the
  // motor, a value of 0 is OFF and 255 is max speed, equivalent of writing HIGH
  // changing which one is bring driven HIGH changes the direction of spin
  digitalWrite(sig3, LOW);
  analogWrite(sig4, 127);
}