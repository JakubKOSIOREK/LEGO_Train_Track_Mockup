// LEGO_train_track_SECTION_A - TRIBRIX TRIPLE SWITCH R40


//LIBRARIES

#include<Servo.h>


//SEMAPHORS

#define led1RED   7
#define led1GREEN 8
#define led2RED   9
#define led2GREEN 10
#define led3RED   11
#define led3GREEN 12


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


void setup() {                  //INITIAL SETTINGS

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
  pinMode(sensor_Tor1, INPUT_PULLUP);
  pinMode(sensor_Tor2, INPUT_PULLUP);
  pinMode(sensor_Tor3, INPUT_PULLUP);

  //SETTINGS
  digitalWrite(led1RED,   LOW);
  digitalWrite(led1GREEN, LOW);
  digitalWrite(led2RED,   LOW);
  digitalWrite(led2GREEN, LOW);
  digitalWrite(led3RED,   LOW);
  digitalWrite(led3GREEN, LOW);
  
  servoL.attach(servoL_Pin);
  servoP.attach(servoP_Pin);
  servoL.write(58);
  servoP.write(100);
  delay(100);
  servoL.detach();
  servoP.detach();
  
  
  
  

    
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 0013){  // TRACK 1 ON-LINE
    
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
    
    //TRACK 1 ON-LINE SEMAPHORS
    digitalWrite(led1RED,   HIGH);  // SEMAPHOR TRACK 1 RED   OFF
    digitalWrite(led1GREEN, LOW);   // SEMAPHOR TRACK 1 GREEN ON
    digitalWrite(led2RED,   LOW);   // SEMAPHOR TRACK 2 RED   ON
    digitalWrite(led2GREEN, HIGH);  // SEMAPHOR TRACK 2 GREEN OFF
    digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
    digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF

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

    //TRACK 2 ON-LINE SEMAPHORS
    digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
    digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
    digitalWrite(led2RED,   HIGH);  // SEMAPHOR TRACK 2 RED   OFF
    digitalWrite(led2GREEN, LOW);   // SEMAPHOR TRACK 2 GREEN ON
    digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
    digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF

  } //end 0023

  if (data == 0033){  // TRACK 3 ON-LINE
    
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

    //TRACK 3 ON-LINE SEMAPHORS
    digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
    digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
    digitalWrite(led2RED,   LOW);   // SEMAPHOR TRACK 2 RED   ON
    digitalWrite(led2GREEN, HIGH);  // SEMAPHOR TRACK 2 GREEN OFF
    digitalWrite(led3RED,   HIGH);  // SEMAPHOR TRACK 3 RED   OFF
    digitalWrite(led3GREEN, LOW);   // SEMAPHOR TRACK 3 GREEN ON
    
  } //end 0033

     
} // end void TxRxData()


void loop() {                   // WORK IN LOOP

 if(Serial.available() > 0) TxRxData();     // EXECUTE void TxRxData()
  
   if (digitalRead(sensor_Tor1) == LOW){    // SENSOR TRACK 1 IMPULSE 91013
      digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
      digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
      Serial.println(91013);
      delay(500);
    } // end sensor_Tor1 == LOW
   
   if (digitalRead(sensor_Tor2) == LOW){    // SENSOR TRACK 2 IMPULSE 91023
    digitalWrite(led2RED,   LOW);   // SEMAPHOR TRACK 2 RED   ON
    digitalWrite(led2GREEN, HIGH);  // SEMAPHOR TRACK 2 GREEN OFF
    Serial.println(91023);
    delay(500);
    } // end sensor_Tor2 == LOW

   if (digitalRead(sensor_Tor3) == LOW){    // SENSOR TRACK 3 IMPULSE 91033
    digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
    digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF
    Serial.println(91033);
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
