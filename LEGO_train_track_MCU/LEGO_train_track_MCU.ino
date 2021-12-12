// LEGO_train_track_MCU


//SENSORS

#define pushButton_1    4
#define pushButton_2    7
#define pushButton_3    8


//VARIABLES

int delayIsSensorLow = 20;
long data;


void setup() {                  // INITIAL SETTINGS

  //COMM
  Serial.begin(38400);
  delay(1000);
    
  //INPUTS
  pinMode (pushButton_1, INPUT_PULLUP);
  pinMode (pushButton_2, INPUT_PULLUP);
  pinMode (pushButton_3, INPUT_PULLUP);
  pinMode (LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("MCU ON-LINE");
  
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 91213){     // SECTION A02 SENSOR TRACK 01 IMPULSE -> 1213 -> TRACK 01 ON-LINE
    Serial.println(1213);
  }
  if (data == 91223){     // SECTION A02 SENSOR TRACK 02 IMPULSE -> 1223 -> TRACK 02 ON-LINE
    Serial.println(1223);
  }
  if (data == 91233){     // SECTION A02 SENSOR TRACK 03 IMPULSE -> 1233 -> TRACK 03 ON-LINE
    Serial.println(1233);
  }
  if (data == 91151){
    Serial.println("SECTION A OFF-LINE");
  }
  if (data == 91150){
    Serial.println("SECTION A ON-LINE");
  }
} // end void TxRxData()

void sensorLow() {              // MCU SENSORS WORK
  if (isSensorLow(pushButton_1)){     // PUSHBUTTON 1 IMPULSE 1013
    delay(500);
    Serial.println(1013);
  }
  if (isSensorLow(pushButton_2)){     // PUSHBUTTON 2 IMPULSE 1023
    delay(500);
    Serial.println(1023);
  }
  if (isSensorLow(pushButton_3)){     // PUSHBUTTON 3 IMPULSE 1033
    delay(500);
    Serial.println(1033);
  }
} // end void sensorLow()

void loop() {                   // WORK IN LOOP
  if (Serial.available() > 0) TxRxData(); // EXECUTE void TxRxData()
  if (                                    // EXECUTE void sensorLow()
      isSensorLow(pushButton_1) ||
      isSensorLow(pushButton_2) ||
      isSensorLow(pushButton_3)
      )
      sensorLow();

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
