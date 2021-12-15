// LEGO_train_track_SECTION_A02 - TRIBRIX TRIPLE SWITCH R40

#include<Servo.h>
#define sensorTrack1  2
#define sensorTrack2  3
#define sensorTrack3  4
Servo servoL;
Servo servoR;
int servoL_Pin = 5;
int servoR_Pin = 6;
int posServoL = 58;
int posServoR = 100;
int delayIsSensorLow = 20;
long data;

void setup() {                  // INITIAL SETTINGS

  //COMM
  Serial.begin(38400);
  delay(1000);
   
  //INPUTS
  pinMode(sensorTrack1, INPUT_PULLUP);
  pinMode(sensorTrack2, INPUT_PULLUP);
  pinMode(sensorTrack3, INPUT_PULLUP);
  
  //SETTINGS
  Serial.println("SECTION A02 ON-LINE");
  
} // end void setup()

void sensorLow(){               // SEKTION A02 SENSORS WORK
  
  if (isSensorLow(sensorTrack1)){   // SENSOR TRACK 01 IMPULSE
    delay(200);
    TRACK_01_setUp();
  }
  if (isSensorLow(sensorTrack2)){   // SENSOR TRACK 02 IMPULSE
    delay(200);
    TRACK_02_setUp();
  }
  if (isSensorLow(sensorTrack3)){   // SENSOR TRACK 03 IMPULSE
    delay(200);
    TRACK_03_setUp();
  }
  
} // end void sensorLow()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 1013) TRACK_01_setUp();  // TRACK 1 ON-LINE
  if (data == 1023) TRACK_02_setUp();  // TRACK 2 ON-LINE
  if (data == 1033) TRACK_03_setUp();  // TRACK 3 ON-LINE
  
} // end void TxRxData()

void TRACK_01_setUp(){          // TRACK 01 ON-LINE
  
  servoL.attach(servoL_Pin);                          // TUTN ON SERVO L
  servoR.attach(servoR_Pin);                          // TUTN ON SERVO R
  for(posServoL =58; posServoL <100; posServoL +=1){  // SERVO L ON THE POSITION
    servoL.write(posServoL);                          // SERVO L ASIDE
  }
  for(posServoR =58; posServoR <100; posServoR +=1){  // SERVO R ON THE POSITION
    servoR.write(posServoR);                          // SERVO R STRAIGHT
  }
  delay(100);
  servoL.detach();                                    // TUTN OFF SERVO L
  servoR.detach();                                    // TUTN OFF SERVO R
  Serial.print("TRACK 01 SWITCHED ON-LINE | ");
  Serial.println(91210);
  
} // end void TRACK_01_setUp()

void TRACK_02_setUp(){          // TRACK 02 ON-LINE
  
  servoL.attach(servoL_Pin);                          // TUTN ON SERVO L
  servoR.attach(servoR_Pin);                          // TUTN ON SERVO R
  for(posServoL =100; posServoL >58; posServoL -=1){  // SERVO L ON THE POSITION
    servoL.write(posServoL);                          // SERVO L STRAIGHT
  }
  for(posServoR =58; posServoR <100; posServoR +=1){  // SERVO R ON THE POSITION
    servoR.write(posServoR);                          // SERVO R STRAIGHT
  }
  delay(100);
  servoL.detach();                                    // TUTN OFF SERVO L
  servoR.detach();                                    // TUTN OFF SERVO R
  Serial.print("TRACK 02 SWITCHED ON-LINE | ");
  Serial.println(91220);
  
} // end void TRACK_02_setUp()

void TRACK_03_setUp(){          // TRACK 03 ON-LINE
  
  servoL.attach(servoL_Pin);                          // TUTN ON SERVO L
  servoR.attach(servoR_Pin);                          // TUTN ON SERVO R
  for(posServoL =100; posServoL >58; posServoL -=1){  // SERVO L ON THE POSITION
    servoL.write(posServoL);                          // SERVO L STRAIGHT
  }
  for(posServoR =100; posServoR >58; posServoR -=1){  // SERVO R ON THE POSITION
    servoR.write(posServoR);                          // SERVO R ASIDE
  }
  delay(100);
  servoL.detach();                                    // TUTN OFF SERVO L
  servoR.detach();                                    // TUTN OFF SERVO R
  Serial.print("TRACK 03 SWITCHED ON-LINE | ");
  Serial.println(91230);
  
} // end void TRACK_03_setUp()

void loop() {                   // WORK IN LOOP

  // EXECUTE void TxRxData()
  if (Serial.available() > 0) TxRxData();

  // EXECUTE void sensorLow()
  if (isSensorLow(sensorTrack1) || isSensorLow(sensorTrack2) || isSensorLow(sensorTrack3)) sensorLow();

} //  end void loop()

bool isSensorLow(int sensor){   // CONTACT VIBRATION PHENOMENO ELIMINATION
  
if (digitalRead(sensor) == LOW){
    delay(delayIsSensorLow);
    if (digitalRead(sensor) == LOW){
      return true;
    }
  }
  return false;
  
} // end bool isSensorLow()
