// LEGO_train_track_MCU


//SENSORS

#define pushButton_1  4
#define pushButton_2  7
#define pushButton_3  8


//VARIABLES

int delayIsSensorLow = 20;
long data;


void setup() {  //INITIAL SETTINGS

  //COMM
  Serial.begin(38400);
  delay(1000);
  Serial.println(9000);
  delay(2000);
  Serial.println(1012);

  //INPUTS
  pinMode (pushButton_1, INPUT_PULLUP);
  pinMode (pushButton_2, INPUT_PULLUP);
  pinMode (pushButton_3, INPUT_PULLUP);
      
} //  end void setup()

void TxRxData(){
  
  data = Serial.parseInt();
  delay(10);

  if (data == 92011){
    Serial.println(2011);
    delay(500);
  }
  
  if (data == 92012){
    Serial.println(2012);
    delay(500);
  }

  if (data == 92013){
    Serial.println(2013);
    delay(500);
  }
} // end void TxRxData()


void loop() { //  WORK IN LOOP

  if(Serial.available() > 0) TxRxData(); //PRZEJŚCIE DO FUNKCJI void TxRxData()
  
  if (digitalRead(pushButton_1)==LOW){  //TOR 1
      delay(500);
      Serial.println(1011);
      }else{
  }

  if (digitalRead(pushButton_2)==LOW){ //TOR 2
      delay(500);
      Serial.println(1012);
      }else{
  }

  if (digitalRead(pushButton_3)==LOW){ //TOR 3
      delay(500);
      Serial.println(1013);
      }else{
  }


} //  end void loop()


bool isSensorLow(int sensor){ //CONTACT VIBRATION PHENOMENO ELIMINATION
  if (digitalRead(sensor) == LOW){
    delay(delayIsSensorLow);
    if (digitalRead(sensor) == LOW){
      return true;
    }
  }
  return false;
} // end bool isSensorLow()
