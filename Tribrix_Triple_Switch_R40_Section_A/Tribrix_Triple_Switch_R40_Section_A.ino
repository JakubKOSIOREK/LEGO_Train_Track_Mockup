// LEGO_train_track_SECTION_A - TRIBRIX TRIPLE SWITCH R40


//LIBRARIES

#include<Servo.h>


//SEMAPHORES

#define led1RED   7
#define led1GREEN 8
#define led2RED   9
#define led2GREEN 10
#define led3RED   11
#define led3GREEN 12


//SENSORS

#define sensorTrack1  2
#define sensorTrack2  3
#define sensorTrack3  4


//SERVO

Servo servoL;
Servo servoR;
int servoL_Pin = 5;
int servoR_Pin = 6;
int posServoL = 58;
int posServoR = 100;


//VARIABLES

int delayIsSensorLow = 20;
long data;
int blinker;
int led1GREENflashing = 0;
int led2GREENflashing = 0;
int led3GREENflashing = 0;
unsigned long time;
unsigned long flashTime = 500;


void setup() {                  // INITIAL SETTINGS

  //COMM
  Serial.begin(38400);
  delay(1000);

  //OUTPUTS
  pinMode(led1RED,    OUTPUT);
  pinMode(led1GREEN,  OUTPUT);
  pinMode(led2RED,    OUTPUT);
  pinMode(led2GREEN,  OUTPUT);
  pinMode(led3RED,    OUTPUT);
  pinMode(led3GREEN,  OUTPUT);

  //INPUTS
  pinMode(sensorTrack1, INPUT_PULLUP);
  pinMode(sensorTrack2, INPUT_PULLUP);
  pinMode(sensorTrack3, INPUT_PULLUP);

  //SETTINGS
  digitalWrite(led1RED,   LOW);
  digitalWrite(led1GREEN, LOW);
  digitalWrite(led2RED,   LOW);
  digitalWrite(led2GREEN, LOW);
  digitalWrite(led3RED,   LOW);
  digitalWrite(led3GREEN, LOW);
  delay(1000);
  digitalWrite(led1RED,   HIGH);
  digitalWrite(led1GREEN, HIGH);
  digitalWrite(led2RED,   HIGH);
  digitalWrite(led2GREEN, HIGH);
  digitalWrite(led3RED,   HIGH);
  digitalWrite(led3GREEN, HIGH);
  delay(1000);
    
  servoL.attach(servoL_Pin);
  servoR.attach(servoR_Pin);
  servoL.write(58);
  servoR.write(100);
  delay(100);
  servoL.detach();
  servoR.detach();

  // TRACK 2 ON-LINE SEMAPHORES
  digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
  digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
  digitalWrite(led2RED,   HIGH);  // SEMAPHOR TRACK 2 RED   OFF
  digitalWrite(led2GREEN, LOW);   // SEMAPHOR TRACK 2 GREEN ON
  digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
  digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF
  
  Serial.println("SECTION A ON-LINE");

} //  end void setup()

void TxRxData() {               // TxRxData TRANSMISION

  data = Serial.parseInt();
  delay(10);

  if (data == 81011 || data == 1013) { // is SEMAPHOR TRACK 1 RED ON
    if (digitalRead(led1RED) == LOW) {
      Serial.println(10111);
    } else {
      Serial.println(10110);
    }
  } // end is SEMAPHOR TRACK 1 RED ON

  if (data == 81021 || data == 1023) { // is SEMAPHOR TRACK 2 RED ON
    if (digitalRead(led2RED) == LOW) {
      Serial.println(10211);
    } else {
      Serial.println(10210);
    }
  } // end is SEMAPHOR TRACK 2 RED ON

  if (data == 81031 || data == 1033) { // is SEMAPHOR TRACK 3 RED ON
    if (digitalRead(led3RED) == LOW) {
      Serial.println(10311);
    } else {
      Serial.println(10310);
    }
  } // end is SEMAPHOR TRACK 3 RED ON

  if (data == 1014) { // TRACK 1 ON-LINE
    led1GREENflashing = 0;          // SEMAPHOR TRACK 1 GREEN STOP FLASHING

    // TRACK 1 SERVO
    servoL.attach(servoL_Pin);
    servoR.attach(servoR_Pin);
    for (posServoL = 100; posServoL > 58; posServoL -= 1) {
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for (posServoR = 100; posServoR > 58; posServoR -= 1) {
      servoR.attach(servoR_Pin);
      servoR.write(posServoR);
    }
    delay(100);
    servoL.detach();
    servoR.detach();

    // TRACK 1 ON-LINE SEMAPHORES
    digitalWrite(led1RED,   HIGH);  // SEMAPHOR TRACK 1 RED   OFF
    digitalWrite(led1GREEN, LOW);   // SEMAPHOR TRACK 1 GREEN ON
    digitalWrite(led2RED,   LOW);   // SEMAPHOR TRACK 2 RED   ON
    digitalWrite(led2GREEN, HIGH);  // SEMAPHOR TRACK 2 GREEN OFF
    digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
    digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF

    Serial.println(91014);
  } // end TRACK 1 ON-LINE

  if (data == 1024) { // TRACK 2 ON-LINE
    led2GREENflashing = 0;          // SEMAPHOR TRACK 2 GREEN STOP FLASHING

    // TRACK 2 SERVO
    servoL.attach(servoL_Pin);
    servoR.attach(servoR_Pin);
    for (posServoL = 100; posServoL > 58; posServoL -= 1) {
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for (posServoR = 58; posServoR < 100; posServoR += 1) {
      servoR.attach(servoR_Pin);
      servoR.write(posServoR);
    }
    delay(100);
    servoL.detach();
    servoR.detach();

    // TRACK 2 ON-LINE SEMAPHORES
    digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
    digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
    digitalWrite(led2RED,   HIGH);  // SEMAPHOR TRACK 2 RED   OFF
    digitalWrite(led2GREEN, LOW);   // SEMAPHOR TRACK 2 GREEN ON
    digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
    digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF

    Serial.println(91024);
  } //end TRACK 2 ON-LINE

  if (data == 1034) { // TRACK 3 ON-LINE
    led3GREENflashing = 0;          // SEMAPHOR TRACK 3 GREEN STOP FLASHING

    // TRACK 3 SERVO
    servoL.attach(servoL_Pin);
    servoR.attach(servoR_Pin);
    for (posServoL = 58; posServoL < 100; posServoL += 1) {
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for (posServoR = 58; posServoR < 100; posServoR += 1) {
      servoR.attach(servoR_Pin);
      servoR.write(posServoR);
    }
    delay(100);
    servoL.detach();
    servoR.detach();

    // TRACK 3 ON-LINE SEMAPHORES
    digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
    digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
    digitalWrite(led2RED,   LOW);   // SEMAPHOR TRACK 2 RED   ON
    digitalWrite(led2GREEN, HIGH);  // SEMAPHOR TRACK 2 GREEN OFF
    digitalWrite(led3RED,   HIGH);  // SEMAPHOR TRACK 3 RED   OFF
    digitalWrite(led3GREEN, LOW);   // SEMAPHOR TRACK 3 GREEN ON

    Serial.println(91034);
  } //end TRACK 3 ON-LINE

} // end void TxRxData()

void sectionAwork() {           // SEKTION A WORK

  if (isSensorLow(sensorTrack1)) {      // SENSOR   TRACK 1 IMPULSE
    led1GREENflashing = 1;              // SEMAPHOR TRACK 1 GREEN START FLASHING
    if (digitalRead(led1RED == HIGH)) { // SEMAPHOR TRACK 1 RED ON
      digitalWrite(led1RED, LOW);
    }
  } // end SENSOR   TRACK 1 IMPULSE

  if (isSensorLow(sensorTrack2)) {      // SENSOR   TRACK 2 IMPULSE
    led2GREENflashing = 1;              // SEMAPHOR TRACK 2 GREEN START FLASHING
    if (digitalRead(led2RED == HIGH)) { // SEMAPHOR TRACK 2 RED ON
      digitalWrite(led2RED, LOW);
    }
  } // end SENSOR   TRACK 2 IMPULSE

  if (isSensorLow(sensorTrack3)) {      // SENSOR   TRACK 3 IMPULSE
    led3GREENflashing = 1;              // SEMAPHOR TRACK 3 GREEN START FLASHING
    if (digitalRead(led3RED == HIGH)) { // SEMAPHOR TRACK 3 RED ON
      digitalWrite(led3RED, LOW);
    }
  } // end SENSOR   TRACK 3 IMPULSE

} // end sectionAwork()

void loop() {                   // WORK IN LOOP

  time = millis();

  // EXECUTE void TxRxData()
  if (Serial.available() > 0) TxRxData();

  // EXECUTE void sectionAwork()
  if (isSensorLow(sensorTrack1) || isSensorLow(sensorTrack2) || isSensorLow(sensorTrack3)) sectionAwork();

  // BLINKER setUP
  if (flashTime < time) {
    blinker++;
    if (blinker > 1)blinker = 0;
    flashTime = time + 500;
  } // end // BLINKER setUP

  // FLASHIG SEMAPHOR 1 GREEN
  if (led1GREENflashing == 1) {
    if (blinker == 0) digitalWrite(led1GREEN, LOW);
    if (blinker == 1) digitalWrite(led1GREEN, HIGH);
  } // end FLASHIG SEMAPHOR 1 GREEN

  // FLASHIG SEMAPHOR 2 GREEN
  if (led2GREENflashing == 1) {
    if (blinker == 0) digitalWrite(led2GREEN, LOW);
    if (blinker == 1) digitalWrite(led2GREEN, HIGH);
  } // end FLASHIG SEMAPHOR 2 GREEN

  // FLASHIG SEMAPHOR 3 GREEN
  if (led3GREENflashing == 1) {
    if (blinker == 0) digitalWrite(led3GREEN, LOW);
    if (blinker == 1) digitalWrite(led3GREEN, HIGH);
  } // end FLASHIG SEMAPHOR 3 GREEN

} //  end void loop()

bool isSensorLow(int sensor) {  // CONTACT VIBRATION PHENOMENO ELIMINATION
  if (digitalRead(sensor) == LOW) {
    delay(delayIsSensorLow);
    if (digitalRead(sensor) == LOW) {
      return true;
    }
  }
  return false;
} // end bool isSensorLow()
