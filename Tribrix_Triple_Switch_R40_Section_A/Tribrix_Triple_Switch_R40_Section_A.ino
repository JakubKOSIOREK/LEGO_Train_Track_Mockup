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

  Serial.println(91000);  //SECTION A READY TO WORK
  delay(500);
    
} //  end void setup()

void TxRxData(){                //TRANSMISJA DANYCH PO UART
  
  data = Serial.parseInt();
  delay(10);

  //  ROZJAZD
  if (data == 1010){  //TOR 1 servoL na wprost, servoP na bok
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
    
    //SEMAFORY GDY TOR 1 ON-LINE
    digitalWrite(led1RED,   HIGH);
    digitalWrite(led1GREEN, LOW);
    digitalWrite(led2RED,   LOW);
    digitalWrite(led2GREEN, HIGH);
    digitalWrite(led3RED,   LOW);
    digitalWrite(led3GREEN, HIGH);
    
    Serial.println(91010);
  } //end 1010

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

    //SEMAFORY GDY TOR 2 ON-LINE
    digitalWrite(led1RED,   LOW);
    digitalWrite(led1GREEN, HIGH);
    digitalWrite(led2RED,   HIGH);
    digitalWrite(led2GREEN, LOW);
    digitalWrite(led3RED,   LOW);
    digitalWrite(led3GREEN, HIGH);
    
    Serial.println(91020);
  } //end 1020

  if (data == 1030){  //TOR 3 servoL na bok, servoP na wprost
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

    //SEMAFORY GDY TOR 3 ON-LINE
    digitalWrite(led1RED,   LOW);
    digitalWrite(led1GREEN, HIGH);
    digitalWrite(led2RED,   LOW);
    digitalWrite(led2GREEN, HIGH);
    digitalWrite(led3RED,   HIGH);
    digitalWrite(led3GREEN, LOW);
    
    Serial.println(91030);
  } //end 1030

  if (data == 2011){  //SEMAFOR 1 NA ZIELONY
    digitalWrite(led1RED,   HIGH);
    digitalWrite(led1GREEN, LOW);
   } //end 2011

  if (data == 2012){  //SEMAFOR 2 NA ZIELONY
    digitalWrite(led2RED,   HIGH);
    digitalWrite(led2GREEN, LOW);
   } //end 2012

  if (data == 2013){  //SEMAFOR 3 NA ZIELONY
    digitalWrite(led3RED,   HIGH);
    digitalWrite(led3GREEN, LOW);
  } //end 2013
      
} // end void TxRxData()


void loop() {                   // WORK IN LOOP


 if(Serial.available() > 0) TxRxData(); //PRZEJŚCIE DO FUNKCJI void TxRxData()
  

   if (digitalRead(sensor_Tor1) == LOW){    //ZMIANA SEMAFOR 1 NA CZERWONE
      digitalWrite(led1RED,   LOW);
      digitalWrite(led1GREEN, HIGH);
      Serial.println(91012);
      delay(500);
    } // end sensor_Tor1 == LOW
   
   if (digitalRead(sensor_Tor2) == LOW){    //ZMIANA SEMAFOR 2 NA CZERWONE
    digitalWrite(led2RED,   LOW);
    digitalWrite(led2GREEN, HIGH);
    Serial.println(91022);
    delay(500);
    } // end sensor_Tor2 == LOW

   if (digitalRead(sensor_Tor3) == LOW){    //ZMIANA SEMAFOR 3 NA CZERWONE
    digitalWrite(led3RED,   LOW);
    digitalWrite(led3GREEN, HIGH);
    Serial.println(91032);
    delay(500);
    } // end sensor_Tor3 == LOW

} //  end void loop()


bool isSensorLow(int sensor){   //CONTACT VIBRATION PHENOMENO ELIMINATION
  if (digitalRead(sensor) == LOW){
    delay(delayIsSensorLow);
    if (digitalRead(sensor) == LOW){
      return true;
    }
  }
  return false;
} // end bool isSensorLow()
