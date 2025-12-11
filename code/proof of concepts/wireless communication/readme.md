# draadloze communicatie proof of concept
minimale hard- en software waarmee aangetoond wordt dat duplex kan gecommuniceerd worden tussen de microcontroller en een [smartphone] (schappen wat niet past), gebruik makend van [Serial Bluetooth Terminal] (in te vullen)
<br />
### configuratie

### opmerkingen

### gebruiksaanwijzing

code:
const int LedPin = 13;  // LED-pin

void setup() {
  Serial.begin(9600);    // USB-seriële monitor
  Serial1.begin(9600);   // Seriële verbinding met Bluetooth-module (HC-05)
  pinMode(LedPin, OUTPUT);
  Serial.println("Bluetooth LED-controller gestart");
}

void loop() {
  if (Serial1.available()) {   // Als er data van Bluetooth komt
    char c = Serial1.read();

    if (c == '1') {
      digitalWrite(LedPin, HIGH);
      Serial.println("LED aan");
    } 
    else if (c == '0') {
      digitalWrite(LedPin, LOW);
      Serial.println("LED uit");
    }
  }
}
