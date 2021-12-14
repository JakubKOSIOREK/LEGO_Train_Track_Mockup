// LEGO_train_track_SECTION_A01 - TRIBRIX TRIPLE SWITCH R40

#include<Servo.h>
#define sensorTrack1  2
#define sensorTrack2  3
#define sensorTrack3  4
#define led1RED       7
#define led1GREEN     8
#define led2RED       9
#define led2GREEN     10
#define led3RED       11
#define led3GREEN     12
Servo servoL;
Servo servoR;
int servoL_Pin = 5;
int servoR_Pin = 6;
int posServoL = 58;
int posServoR = 100;
int delayIsSensorLow = 20;
long data;
int blinker;
int led1GREENflashing = 0;
int led2GREENflashing = 0;
int led3GREENflashing = 0;
unsigned long time;
unsigned long flashTime = 500;
int trackStatus[3];

void setup() {                  // SEKTION A01 INITIAL SETTINGS

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
  Serial.println("SECTION A01 ON-LINE");
  Serial.print("SECTION A01 STATUS        | ");
  sectionStatus();                    // EXECUTE void sectionStatus()

} //  end void setup()

void sectionStatus(){           // SECTION A01 STATUS
  
  Serial.print(trackStatus[0]);
  Serial.print(" | ");
  Serial.print(trackStatus[1]);
  Serial.print(" | ");
  Serial.print(trackStatus[2]);
  Serial.println(" | ");
  
} // end void sectionStatus()

void sensorLow() {              // SEKTION A01 SENSORS WORK
  
  if(isSensorLow(sensorTrack1)){      // SENSOR TRACK 01 IMULSE -> 91113
    if (trackStatus[0] == 0){
      trackStatus[0] = 1;               // TRACK 01 STATUS OFF-LINE
      led1GREENflashing = 1;            // SEMAPHOR TRACK 01 GREEN START FLASHING
      digitalWrite(led1RED, LOW);       // SEMAPHOR TRACK 01 RED OFF
      Serial.print("SENSOR TRACK 01 IMULSE    | ");
      sectionStatus();
      Serial.println(91113);
    }
  }
  if(isSensorLow(sensorTrack2)){      // SENSOR TRACK 02 IMULSE -> 91123
    if (trackStatus[1] == 0){    
      trackStatus[1] = 1;               // TRACK 02 STATUS OFF-LINE
      led2GREENflashing = 1;            // SEMAPHOR TRACK 02 GREEN START FLASHING
      digitalWrite(led2RED, LOW);       // SEMAPHOR TRACK 02 RED OFF
      Serial.print("SENSOR TRACK 02 IMULSE    | ");
      sectionStatus();
      Serial.println(91123);
    }
  }
  if(isSensorLow(sensorTrack3)){      // SENSOR TRACK 03 IMULSE -> 91133
    if (trackStatus[2] == 0){        
      trackStatus[2] = 1;               // TRACK 03 STATUS OFF-LINE
      led3GREENflashing = 1;            // SEMAPHOR TRACK 03 GREEN START FLASHING
      digitalWrite(led3RED, LOW);       // SEMAPHOR TRACK 03 RED OFF
      Serial.print("SENSOR TRACK 03 IMULSE    | ");
      sectionStatus();
      Serial.println(91133);
    }
  }
  
} // end void sensorLow()

void TxRxData() {               // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if(data == 1013 || data == 1213) TRACK_01_setUp();  // TRACK 01 ON LINE
  if(data == 1023 || data == 1223) TRACK_02_setUp();  // TRACK 02 ON LINE
  if(data == 1033 || data == 1233) TRACK_03_setUp();  // TRACK 02 ON LINE
  
} // end void TxRxData()

void TRACK_01_setUp(){          // TRACK 01 ON-LINE -> 91110
  if (trackStatus[0] == 1){
      trackStatus[0] = 0;
      led1GREENflashing = 0;                                  // SEMAPHOR TRACK 01 GREEN STOP FLASHINK
      digitalWrite(led1RED,   HIGH);                          // SEMAPHOR TRACK 01 RED   OFF
      digitalWrite(led2RED,   LOW);                           // SEMAPHOR TRACK 02 RED   ON
      digitalWrite(led3RED,   LOW);                           // SEMAPHOR TRACK 03 RED   ON
      digitalWrite(led1GREEN, LOW);                           // SEMAPHOR TRACK 01 GREEN ON
      digitalWrite(led2GREEN, HIGH);                          // SEMAPHOR TRACK 02 GREEN OFF
      digitalWrite(led3GREEN, HIGH);                          // SEMAPHOR TRACK 03 GREEN OFF
      servoL.attach(servoL_Pin);                              // TUTN ON SERVO L
      servoR.attach(servoR_Pin);                              // TUTN ON SERVO R
      for (posServoL = 100; posServoL > 58; posServoL -= 1){  // SERVO L ON THE POSITION
        servoL.write(posServoL);                              // SERVO L STRAIGHT
      }
      for (posServoR = 100; posServoR > 58; posServoR -= 1){  // SERVO R ON THE POSITION
        servoR.write(posServoR);                              // SERVO R ASIDE
      }
      delay(100);
      servoL.detach();                                        // TUTN OFF SERVO L
      servoR.detach();                                        // TUTN OFF SERVO R
      Serial.print("TRACK 01 SWITCHED ON-LINE | ");
      sectionStatus();
      Serial.println(91110);
  }
} // end void TRACK_01_setUp()

void TRACK_02_setUp(){          // TRACK 02 ON-LINE -> 91120
  if (trackStatus[1] == 1){
      trackStatus[1] = 0;
      led2GREENflashing = 0;                                  // SEMAPHOR TRACK 02 GREEN STOP FLASHINK
      digitalWrite(led1RED,   LOW);                           // SEMAPHOR TRACK 01 RED   ON
      digitalWrite(led2RED,   HIGH);                          // SEMAPHOR TRACK 02 RED   OFF
      digitalWrite(led3RED,   LOW);                           // SEMAPHOR TRACK 03 RED   ON
      digitalWrite(led1GREEN, HIGH);                          // SEMAPHOR TRACK 01 GREEN OFF
      digitalWrite(led2GREEN, LOW);                           // SEMAPHOR TRACK 02 GREEN ON
      digitalWrite(led3GREEN, HIGH);                          // SEMAPHOR TRACK 03 GREEN OFF
      servoL.attach(servoL_Pin);                              // TUTN ON SERVO L
      servoR.attach(servoR_Pin);                              // TUTN ON SERVO R
      for (posServoL = 100; posServoL > 58; posServoL -= 1) { // SERVO L ON THE POSITION
      servoL.write(posServoL);                                // SERVO L STRAIGHT
      }
      for (posServoR = 58; posServoR < 100; posServoR += 1) { // SERVO R ON THE POSITION
        servoR.write(posServoR);                              // SERVO R STRAIGHT
      }
      delay(100);
      servoL.detach();                                        // TUTN OFF SERVO L
      servoR.detach();                                        // TUTN OFF SERVO R
      Serial.print("TRACK 02 SWITCHED ON-LINE | ");
      sectionStatus();
      Serial.println(91120);
  }
} // end void TRACK_02_setUp()

void TRACK_03_setUp(){          // TRACK 03 ON-LINE -> 91130
  if (trackStatus[2] == 1){
      trackStatus[2] = 0;
      led3GREENflashing = 0;                                  // SEMAPHOR TRACK 03 GREEN STOP FLASHINK
      digitalWrite(led1RED,   LOW);                           // SEMAPHOR TRACK 01 RED   ON
      digitalWrite(led2RED,   LOW);                           // SEMAPHOR TRACK 02 RED   ON
      digitalWrite(led3RED,   HIGH);                          // SEMAPHOR TRACK 03 RED   OFF
      digitalWrite(led1GREEN, HIGH);                          // SEMAPHOR TRACK 01 GREEN OFF
      digitalWrite(led2GREEN, HIGH);                          // SEMAPHOR TRACK 02 GREEN OFF
      digitalWrite(led3GREEN, LOW);                           // SEMAPHOR TRACK 03 GREEN ON
      servoL.attach(servoL_Pin);                              // TUTN ON SERVO L
      servoR.attach(servoR_Pin);                              // TUTN ON SERVO R
      for (posServoL = 58; posServoL < 100; posServoL += 1) { // SERVO L ON THE POSITION
        servoL.write(posServoL);                              // SERVO L ASIDE
      }
      for (posServoR = 58; posServoR < 100; posServoR += 1) { // SERVO R ON THE POSITION
        servoR.write(posServoR);                              // SERVO R STRAIGHT
      }
      delay(100);
      servoL.detach();                                        // TUTN OFF SERVO L
      servoR.detach();                                        // TUTN OFF SERVO R
      Serial.print("TRACK 03 SWITCHED ON-LINE | ");
      sectionStatus();
      Serial.println(91130);
  }
} // end void TRACK_03_setUp()

void loop() {                   // WORK IN LOOP

  time = millis();

  // EXECUTE void TxRxData()
  if (Serial.available() > 0) TxRxData();

  // EXECUTE void sensorLow()
  if (isSensorLow(sensorTrack1) || isSensorLow(sensorTrack2) || isSensorLow(sensorTrack3)) sensorLow();

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
