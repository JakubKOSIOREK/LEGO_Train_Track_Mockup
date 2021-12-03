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
  
  servoL.attach(servoL_Pin);
  servoR.attach(servoR_Pin);
  servoL.write(58);
  servoR.write(100);
  delay(100);
  servoL.detach();
  servoR.detach();

  Serial.println("SECTION A ON-LINE");
      
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 81012 || data == 1013){ // is SEMAPHOR TRACK 1 GREEN ON & RED OFF
    if (digitalRead(led1GREEN) == LOW && (digitalRead(led1RED) == HIGH || digitalRead(led1RED) == LOW)){
      Serial.println(10121);
    }else{
      Serial.println(10120);
    }
  } // end is SEMAPHOR TRACK 1 GREEN ON & RED OFF

  if (data == 81022 || data == 1023){ // is SEMAPHOR TRACK 2 GREEN ON & RED OFF
    if (digitalRead(led2GREEN) == LOW && (digitalRead(led2RED) == HIGH || digitalRead(led2RED) == LOW)){
      Serial.println(10221);
    }else{
      Serial.println(10220);
    }
  } // end is SEMAPHOR TRACK 2 GREEN ON & RED OFF

  if (data == 81032 || data == 1033){ // is SEMAPHOR TRACK 3 GREEN ON & RED OFF
    if (digitalRead(led3GREEN) == LOW && (digitalRead(led3RED) == HIGH || digitalRead(led3RED) == LOW)){
      Serial.println(10321);
    }else{
      Serial.println(10320);
    }
  } // end is SEMAPHOR TRACK 3 GREEN ON & RED OFF


  if (data == 1014){  // TRACK 1 ON-LINE
  
    // TRACK 1 SERVO
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
    
    // TRACK 1 ON-LINE SEMAPHORS
    digitalWrite(led1RED,   HIGH);  // SEMAPHOR TRACK 1 RED   OFF
    digitalWrite(led1GREEN, LOW);   // SEMAPHOR TRACK 1 GREEN ON
    digitalWrite(led2RED,   LOW);   // SEMAPHOR TRACK 2 RED   ON
    digitalWrite(led2GREEN, HIGH);  // SEMAPHOR TRACK 2 GREEN OFF
    digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
    digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF

    Serial.println(91014);
  } // end TRACK 1 ON-LINE

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

    // TRACK 2 ON-LINE SEMAPHORS
    digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
    digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
    digitalWrite(led2RED,   HIGH);  // SEMAPHOR TRACK 2 RED   OFF
    digitalWrite(led2GREEN, LOW);   // SEMAPHOR TRACK 2 GREEN ON
    digitalWrite(led3RED,   LOW);   // SEMAPHOR TRACK 3 RED   ON
    digitalWrite(led3GREEN, HIGH);  // SEMAPHOR TRACK 3 GREEN OFF

    Serial.println(91024);
  } //end TRACK 2 ON-LINE

  if (data == 1034){  // TRACK 3 ON-LINE

    // TRACK 3 SERVO
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

    // TRACK 3 ON-LINE SEMAPHORS
    digitalWrite(led1RED,   LOW);   // SEMAPHOR TRACK 1 RED   ON
    digitalWrite(led1GREEN, HIGH);  // SEMAPHOR TRACK 1 GREEN OFF
    digitalWrite(led2RED,   LOW);   // SEMAPHOR TRACK 2 RED   ON
    digitalWrite(led2GREEN, HIGH);  // SEMAPHOR TRACK 2 GREEN OFF
    digitalWrite(led3RED,   HIGH);  // SEMAPHOR TRACK 3 RED   OFF
    digitalWrite(led3GREEN, LOW);   // SEMAPHOR TRACK 3 GREEN ON

    Serial.println(91034);
  } //end TRACK 3 ON-LINE


if (data == 1010){

//  led1GREENflashing = 0 // OFF
}





//  if (data == 1003){  // which TRACK is available
//    if(digitalRead(led1RED == LOW) && digitalRead(led1GREEN == LOW)){
//      // to tor 1 zajęty
//    }
//  }



} // end void TxRxData()


void loop() {                   // WORK IN LOOP

 time = millis();
 
 if(Serial.available() > 0) TxRxData();     // EXECUTE void TxRxData()
  
   if (digitalRead(sensorTrack1) == LOW){    // SENSOR TRACK 1 IMPULSE
      if (digitalRead(led1RED == HIGH)){
        digitalWrite(led1RED, LOW);
        }else{}
//          led1GREENflashing = 1; // ON
        Serial.println(10111);
    } // end SENSOR TRACK 1 IMPULSE 91013
   
   if (digitalRead(sensorTrack2) == LOW){    // SENSOR TRACK 2 IMPULSE
      if (digitalRead(led2RED == HIGH)){
        digitalWrite(led2RED, LOW);
      }else{
        
      }
    } // end SENSOR TRACK 2 IMPULSE 91023

   if (digitalRead(sensorTrack3) == LOW){    // SENSOR TRACK 3 IMPULSE
      if (digitalRead(led3RED == HIGH)){
        digitalWrite(led3RED, LOW);
      }else{
        
      }
    } // end SENSOR TRACK 3 IMPULSE 91033

  if (flashTime < time){                     // BLINKER setUP
    blinker++;
    if (blinker > 1)blinker = 0;
    flashTime = time + 500;
  }

//  if (led1GREENflashing == 1){               // FLASHIG SEMAPHOR 1 GREEN 
//    if (blinker == 0) digitalWrite(led1GREEN , LOW);
//    if (blinker == 1) digitalWrite(led1GREEN), HIGH);
//  }
  
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
