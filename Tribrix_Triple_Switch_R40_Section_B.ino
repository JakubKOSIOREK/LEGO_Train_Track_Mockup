// LEGO_train_track_SECTION_B - TRIBRIX TRIPLE SWITCH R40


//BIBLIOTEKI
#include<Servo.h>

//SEMAFORY
#define led1RED   7
#define led1GREEN 8
#define led2RED   9
#define led2GREEN 10
#define led3RED   11
#define led3GREEN 12

//CZUJNIKI
#define sensor_Tor1  2
#define sensor_Tor2  3
#define sensor_Tor3  4

//SERVA
Servo servoL;
Servo servoP;
int servoL_Pin = 5;
int servoP_Pin = 6;
int posServoL = 58;
int posServoP = 100;

//ZMIENNE
int delayIsSensorLow = 20;
int data;



//ZEGAR
unsigned long czas;


//USTAWIENIA POCZĄTKOWE DLA SEKCJI B
void setup() {

  //COMM
  Serial.begin(38400);
  delay(1000);
  Serial.println(92000);
  
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
  digitalWrite(led1GREEN, HIGH);
  digitalWrite(led2RED,   HIGH);
  digitalWrite(led2GREEN, LOW);
  digitalWrite(led3RED,   LOW);
  digitalWrite(led3GREEN, HIGH);
  servoL.attach(servoL_Pin);
  servoP.attach(servoP_Pin);
  servoL.write(58);
  servoP.write(100);
  delay(100);
  servoL.detach();
  servoP.detach();
    
} //  end void setup()

void TxRxData(){
  
  data = Serial.parseInt();
  delay(10);
//  if (data == 1000){
//    Serial.println(92000);
//  }

  //  ROZJAZD
  if (data == 1011){                //TOR 1 servoL na wprost, servoP na bok
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
    digitalWrite(led1RED,   HIGH);
    digitalWrite(led1GREEN, LOW);
    digitalWrite(led2RED,   LOW);
    digitalWrite(led2GREEN, HIGH);
    digitalWrite(led3RED,   LOW);
    digitalWrite(led3GREEN, HIGH);
    Serial.println(92011);
  } //end 1011

  if (data == 1012){                //TOR 2 servoL na wprost, servoP na wprost
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
    digitalWrite(led1RED,   LOW);
    digitalWrite(led1GREEN, HIGH);
    digitalWrite(led2RED,   HIGH);
    digitalWrite(led2GREEN, LOW);
    digitalWrite(led3RED,   LOW);
    digitalWrite(led3GREEN, HIGH);
    Serial.println(92012);
  } //end 1012

  if (data == 1013){                //TOR 3 servoL na bok, servoP na wprost
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
    digitalWrite(led1RED,   LOW);
    digitalWrite(led1GREEN, HIGH);
    digitalWrite(led2RED,   LOW);
    digitalWrite(led2GREEN, HIGH);
    digitalWrite(led3RED,   HIGH);
    digitalWrite(led3GREEN, LOW);
    Serial.println(92013);
  } //end 1013


  
} // end void TxRxData()


void loop() {

 czas = millis();
 if(Serial.available() > 0) TxRxData();
  

   if (digitalRead(sensor_Tor1) == LOW){
    digitalWrite(led1RED,   LOW);
    digitalWrite(led1GREEN, HIGH);
    Serial.println(92021);
    delay(500);
    } // end sensor_Tor1 == LOW
   
   if (digitalRead(sensor_Tor2) == LOW){
    digitalWrite(led2RED,   LOW);
    digitalWrite(led2GREEN, HIGH);
    Serial.println(92022);
    delay(500);
    } // end sensor_Tor2 == LOW

   if (digitalRead(sensor_Tor3) == LOW){
    digitalWrite(led3RED,   LOW);
    digitalWrite(led3GREEN, HIGH);
    Serial.println(92023);
    delay(500);
    } // end sensor_Tor3 == LOW

} //  end void loop()

// ELIMINACJA ZJAWISKA DRGAŃ STYKÓW
bool isSensorLow(int sensor){
  if (digitalRead(sensor) == LOW){
    delay(delayIsSensorLow);
    if (digitalRead(sensor) == LOW){
      return true;
    }
  }
  return false;
} // end bool isSensorLow()
