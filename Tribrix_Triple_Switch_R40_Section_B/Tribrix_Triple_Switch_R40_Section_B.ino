// LEGO_train_track_SECTION_B - TRIBRIX TRIPLE SWITCH R40


//LIBRARIES

#include<Servo.h>


//SENSORS

#define sensor_Tor1  2
#define sensor_Tor2  3
#define sensor_Tor3  4


//SERVO

Servo servoL;
Servo servoP;
int servoL_Pin = 5;
int servoP_Pin = 6;
int posServoL = 58;
int posServoP = 100;


//VARIABLES

int delayIsSensorLow = 20;
int data;


void setup() {                  // INITIAL SETTINGS

  //COMM
  Serial.begin(38400);
  delay(1000);
   
  //INPUTS
  pinMode(sensor_Tor1, INPUT_PULLUP);
  pinMode(sensor_Tor2, INPUT_PULLUP);
  pinMode(sensor_Tor3, INPUT_PULLUP);
  
  //SETTINGS

  servoL.attach(servoL_Pin);
  servoP.attach(servoP_Pin);
  servoL.write(58);
  servoP.write(100);
  delay(100);
  servoL.detach();
  servoP.detach();

  Serial.println(92000);
  delay(500);
    
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 0013){  // TRACK 1 ON-LINE
    
    servoL.attach(servoL_Pin);
    servoP.attach(servoP_Pin);
    for(posServoL =58; posServoL <100; posServoL +=1){
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for(posServoP =58; posServoP <100; posServoP +=1){
      servoP.attach(servoP_Pin);
      servoP.write(posServoP);
    }
    delay(100);
    servoL.detach();
    servoP.detach();

  } //end 0013

  if (data == 0023){  // TRACK 2 ON-LINE
    servoL.attach(servoL_Pin);
    servoP.attach(servoP_Pin);
    for(posServoL =100; posServoL >58; posServoL -=1){
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for(posServoP =58; posServoP <100; posServoP +=1){
      servoP.attach(servoP_Pin);
      servoP.write(posServoP);
    }
    delay(100);
    servoL.detach();
    servoP.detach();

  } //end 0023
  
  if (data == 0033){  // TRACK 3 ON-LINE
    servoL.attach(servoL_Pin);
    servoP.attach(servoP_Pin);
    for(posServoL =100; posServoL >58; posServoL -=1){
      servoL.attach(servoL_Pin);
      servoL.write(posServoL);
    }
    for(posServoP =100; posServoP >58; posServoP -=1){
      servoP.attach(servoP_Pin);
      servoP.write(posServoP);
    }
    delay(100);
    servoL.detach();
    servoP.detach();

  } //end 0033

} // end void TxRxData()


void loop() {                   // WORK IN LOOP

 if(Serial.available() > 0) TxRxData();   // EXECUTE void TxRxData()

 if (digitalRead(sensor_Tor1) == LOW){    // SENSOR TRACK 1 IMPULSE 92013
    Serial.println(92013);
    delay(500);
    } // end sensor_Tor1 == LOW

 if (digitalRead(sensor_Tor2) == LOW){    // SENSOR TRACK 2 IMPULSE 92023
    Serial.println(92023);
    delay(500);
    } // end sensor_Tor2 == LOW

 if (digitalRead(sensor_Tor3) == LOW){    // SENSOR TRACK 3 IMPULSE 92033
    Serial.println(92033);
    delay(500);
    } // end sensor_Tor3 == LOW

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
