// LEGO_train_track_SECTION_B - TRIBRIX TRIPLE SWITCH R40


//LIBRARIES

#include<Servo.h>


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


void setup() {                  // INITIAL SETTINGS

  //COMM
  Serial.begin(38400);
  delay(1000);
   
  //INPUTS
  pinMode(sensorTrack1, INPUT_PULLUP);
  pinMode(sensorTrack2, INPUT_PULLUP);
  pinMode(sensorTrack3, INPUT_PULLUP);
  
  //SETTINGS

  servoL.attach(servoL_Pin);
  servoR.attach(servoR_Pin);
  servoL.write(58);
  servoR.write(100);
  delay(100);
  servoL.detach();
  servoR.detach();

  Serial.println("SECTION B ON-LINE");
    
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 1014){  // TRACK 1 ON-LINE

    // TRACK 1 SERVO
    servoL.attach(servoL_Pin);
    servoR.attach(servoR_Pin);
    for(posServoL =58; posServoL <100; posServoL +=1){
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for(posServoR =58; posServoR <100; posServoR +=1){
      servoR.attach(servoR_Pin);
      servoR.write(posServoR);
    }
    delay(100);
    servoL.detach();
    servoR.detach();
    
  } //end TRACK 1 ON-LINE

  if (data == 1024){  // TRACK 2 ON-LINE
  
    // TRACK 2 SERVO
    servoL.attach(servoL_Pin);
    servoR.attach(servoR_Pin);
    for(posServoL =100; posServoL >58; posServoL -=1){
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for(posServoR =58; posServoR <100; posServoR +=1){
      servoR.attach(servoR_Pin);
      servoR.write(posServoR);
    }
    delay(100);
    servoL.detach();
    servoR.detach();
    
  } //end TRACK 2 ON-LINE
  
  if (data == 1034){  // TRACK 3 ON-LINE
    
    // TRACK 3 SERVO  
    servoL.attach(servoL_Pin);
    servoR.attach(servoR_Pin);
    for(posServoL =100; posServoL >58; posServoL -=1){
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for(posServoR =100; posServoR >58; posServoR -=1){
      servoR.attach(servoR_Pin);
      servoR.write(posServoR);
    }
    delay(100);
    servoL.detach();
    servoR.detach();

  } //end TRACK 3 ON-LINE

} // end void TxRxData()


void sectionBwork(){        // SECTION B WORK
  
  if (isSensorLow(sensorTrack1)){   // SENSOR TRACK 1 IMPULSE 2013
    Serial.println(2013);
    delay(500);
    } // end sensorTrack1 == LOW

 if (isSensorLow(sensorTrack2)){    // SENSOR TRACK 2 IMPULSE 2023
    Serial.println(2023);
    delay(500);
    } // end sensorTrack2 == LOW

 if (isSensorLow(sensorTrack3)){    // SENSOR TRACK 3 IMPULSE 2033
    Serial.println(2033);
    delay(500);
    } // end sensorTrack3 == LOW
    
} // end sectionBwork()


void loop() {                   // WORK IN LOOP

  // EXECUTE void TxRxData()
  if (Serial.available() > 0) TxRxData();

  // EXECUTE void sectionAwork()
  if (isSensorLow(sensorTrack1) || isSensorLow(sensorTrack2) || isSensorLow(sensorTrack3)) sectionBwork();

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
