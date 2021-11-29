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

void TxRxData(){                // TRANSMISJA DANYCH PO UART
  
  data = Serial.parseInt();
  delay(10);


  //  ROZJAZD

  if (data == 1010){  //TOR 1 servoL na wprost, servoP na bok
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
//    Serial.println(92010);
//    delay(500);
  } //end 1011

  if (data == 1020){  //TOR 2 servoL na wprost, servoP na wprost
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
//    Serial.println(92020);
//    delay(500);
  } //end 1012
  
  if (data == 1030){  //TOR 3 servoL na bok, servoP na wprost
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
//    Serial.println(92030);
//    delay(500);
  } //end 1013

} // end void TxRxData()


void loop() {                   // WORK IN LOOP


 if(Serial.available() > 0) TxRxData(); //PRZEJŚCIE DO FUNKCJI void TxRxData()
  

 if (digitalRead(sensor_Tor1) == LOW){    //ZMIANA SEMAFOR 1 NA ZIELONE
    Serial.println(92011);
    delay(500);
    } // end sensor_Tor1 == LOW

 if (digitalRead(sensor_Tor2) == LOW){    //ZMIANA SEMAFOR 1 NA ZIELONE
    Serial.println(92012);
    delay(500);
    } // end sensor_Tor2 == LOW

 if (digitalRead(sensor_Tor3) == LOW){    //ZMIANA SEMAFOR 1 NA ZIELONE
    Serial.println(92013);
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
