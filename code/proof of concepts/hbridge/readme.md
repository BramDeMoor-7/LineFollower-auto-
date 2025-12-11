# H-Bridge proof of concept

minimale hard- & software + stappenplan dat aantoont dat 2 motoren onafhankelijk van elkaar kunnen draaien, en (traploos) regelbaar zijn in snelheid en draairichting.

Vergeet niet de eep pin van de drv8833 aan te sluiten aan je 5V van je ardruino anders zal je drv8833 module in een slaap modus blijven een geen uitgang doorgeven.
code:

const int sig1 = 10;
const int sig2 = 9;
const int sig3 = 6;
const int sig4 = 5;


void setup() {

pinMode(sig1, OUTPUT);
pinMode(sig2, OUTPUT);
pinMode(sig3, OUTPUT);
pinMode(sig4, OUTPUT);

digitalWrite(sig1, LOW);
digitalWrite(sig2, LOW);
digitalWrite(sig3, LOW);
digitalWrite(sig4, LOW);

}

void loop() {
  

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

  digitalWrite(sig1, LOW);
  digitalWrite(sig2, LOW);
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, LOW);
}

void motorA_CCW() {
 
  digitalWrite(sig1, HIGH);
  digitalWrite(sig2, LOW);
}

void motorA_CW() {

  digitalWrite(sig1, LOW);
  digitalWrite(sig2, HIGH);
}

void motorA_CCW_Half() {

  analogWrite(sig1, 127);
  digitalWrite(sig2, LOW);
}

void motorA_CW_Half() {

  digitalWrite(sig1, LOW);
  analogWrite(sig2, 127);
}

void motorB_CCW() {

  digitalWrite(sig3, HIGH);
  digitalWrite(sig4, LOW);
}

void motorB_CW() {

  digitalWrite(sig3, LOW);
  digitalWrite(sig4, HIGH);
}

void motorB_CCW_Half() {

  analogWrite(sig3, 127);
  digitalWrite(sig4, LOW);
}

void motorB_CW_Half() {

  digitalWrite(sig3, LOW);
  analogWrite(sig4, 127);
}
