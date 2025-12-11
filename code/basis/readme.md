# basis programma

volgende zaken werken samen in dit template project  

* instelbare parameters mbv. SerialCommands 
  * cyclus tijd
  * debug on/off
  * start/stop
* parameters worden opgeslagen in eeprom geheugen
* start/stop kan ook geactiveerd worden mbv. een externe interrupt
* draadloze communicatie

Met behulp van de cyclus kan je bvb. een knipperende led programmeren.

#include "SerialCommand.h"
#include "EEPROMAnything.h"

#define SerialPort Serial1
#define Baudrate 9600
#define DebugPort Serial

SerialCommand sCmd(SerialPort);
bool run = false;
unsigned long previous = 0;
unsigned long calculationTime = 0;

#define NUM_SENSORS 6
const uint8_t sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5};

struct param_t {
  unsigned long cycleTime;
  int black[6];
  int white[6];
  int power;
  float diff;
  float kp;
} params;

float debugPosition;

void onUnknownCommand(char *command);
void onSet();
void onDebug();
void onCalibrate();
void onRun();
void onOff();

void setup() {
  DebugPort.begin(115200);
  SerialPort.begin(Baudrate);

  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.addCommand("on", onRun);
  sCmd.addCommand("off", onOff);
  sCmd.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);
  if (params.cycleTime == 0) params.cycleTime = 5000;

  SerialPort.println("ready");
}

void loop() {
  sCmd.readSerial();
  unsigned long current = micros();

  if (current - previous >= params.cycleTime) {
    previous = current;

    int normalised[NUM_SENSORS];
    int bin[NUM_SENSORS];

    for (int i = 0; i < NUM_SENSORS; i++) {
      int val = analogRead(sensorPins[i]);
      normalised[i] = map(val, params.black[i], params.white[i], 0, 1000);
      normalised[i] = constrain(normalised[i], 0, 1000);
      bin[i] = (normalised[i] >= 700) ? 1 : 0;
  }

  unsigned long diff = micros() - current;
  if (diff > calculationTime) calculationTime = diff;
}

void onUnknownCommand(char *command) {
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet() {
  char* param = sCmd.next();
  char* value = sCmd.next();

  if (strcmp(param, "cycle") == 0) params.cycleTime = atol(value);
  else if (strcmp(param, "power") == 0) params.power = atol(value);
  else if (strcmp(param, "diff") == 0) params.diff = atof(value);
  else if (strcmp(param, "kp") == 0) params.kp = atof(value);

  EEPROM_writeAnything(0, params);
  SerialPort.println("ok");
}

void onDebug() {
  SerialPort.print("position (mm): ");
  SerialPort.println(debugPosition);

  SerialPort.println("cycle time: ");
  SerialPort.println(params.cycleTime);

  SerialPort.print("black: ");
  for (int i = 0; i < 6; i++) { SerialPort.print(params.black[i]); SerialPort.print(" "); }
  SerialPort.println();

  SerialPort.print("white: ");
  for (int i = 0; i < 6; i++) { SerialPort.print(params.white[i]); SerialPort.print(" "); }
  SerialPort.println();

  SerialPort.println("power: ");
  SerialPort.println(params.power);

  SerialPort.println("diff: ");
  SerialPort.println(params.diff);

  SerialPort.println("kp: ");
  SerialPort.println(params.kp);
}

void onCalibrate() {
  char* param = sCmd.next();
  if (!param) return;

  if (strcmp(param, "black") == 0)
    for (int i = 0; i < 6; i++) params.black[i] = analogRead(sensorPins[i]);

  else if (strcmp(param, "white") == 0)
    for (int i = 0; i < 6; i++) params.white[i] = analogRead(sensorPins[i]);

  EEPROM_writeAnything(0, params);
  SerialPort.println("done");
}

void onRun() {
  run = true;
  SerialPort.println("run mode enabled");
}

void onOff() {
  run = false;
  SerialPort.println("run mode disabled");
}

