#include <QTRSensors.h>

#define NUM_SENSORS 6
const uint8_t sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5};

QTRSensors qtr;
unsigned int sensorValues[NUM_SENSORS];

// Boogberekening aanpassen voor 6 sensoren
// 122 mm totale breedte => 5 stappen ertussen
const float arcTotal = 40;
const float stepMM   = arcTotal / 5.0;   // ≈ 24.4 mm

// ---------- berekening lijnpositie (gewogen gemiddelde) ----------
float getLinePosition(int bin[NUM_SENSORS]) {
  float weightedSum = 0;
  float weightSum   = 0;

  for (int i = 0; i < NUM_SENSORS; i++) {
    int w = bin[i];   // 0 of 1
    if (!w) continue;

    // midden tussen index 2 en 3 = 0 mm
    float posMM = -((float)i - 2.5) * stepMM;

    weightedSum += w * posMM;
    weightSum   += w;
  }

  if (weightSum == 0) return 0;

  return weightedSum / weightSum;
}

// ---------- setup ----------
void setup() {
  Serial.begin(9600);
  delay(500);

  qtr.setTypeAnalog();
  qtr.setSensorPins(sensorPins, NUM_SENSORS);

  Serial.println("Kalibreren... Beweeg de sensor over wit en zwart.");

  for (int i = 0; i < 250; i++) {
    qtr.calibrate();
    delay(20);
  }

  Serial.println("Kalibratie klaar!");
  Serial.println("Start met meten...");
}

// ---------- loop ----------
void loop() {

  // Gecalibreerde waarden van 0 (wit) t/m 1000 (zwart)
  qtr.readCalibrated(sensorValues);

  int bin[NUM_SENSORS];

  // zwart/wit binaire mapping
  for (int i = 0; i < NUM_SENSORS; i++) {
    bin[i] = (sensorValues[i] >= 700) ? 1 : 0;
  }

  // Ongefilterde positie in mm
  float rawPos = getLinePosition(bin);

  // Smoothing
  static float filtPos = 0;
  static bool firstRun = true;
  const float alpha = 0.7;

  if (firstRun) {
    filtPos = rawPos;
    firstRun = false;
  } else {
    filtPos = alpha * filtPos + (1.0 - alpha) * rawPos;
  }

  // ---------- debug ----------
  Serial.print("SENSOR: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  Serial.print(" | BIN: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(bin[i]);
    Serial.print(" ");
  }

  Serial.print(" | raw mm = ");
  Serial.print(rawPos);

  Serial.print(" | filt mm = ");
  Serial.println(filtPos);

  delay(100);
}
