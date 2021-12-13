// LEGO_train_track_MCU


//SENSORS
#define sensorMCU01     2
#define pushButton_1    4
#define pushButton_2    7
#define pushButton_3    8


//VARIABLES

int delayIsSensorLow = 20;
long data;
int sectionA01status[3] = {1, 0, 1};
int sectionA02status[3] = {1, 0, 1};

void setup() {                  // INITIAL SETTINGS

  //COMM
  Serial.begin(38400);
  delay(1000);
    
  //INPUTS
  pinMode (sensorMCU01, INPUT_PULLUP);
  pinMode (pushButton_1, INPUT_PULLUP);
  pinMode (pushButton_2, INPUT_PULLUP);
  pinMode (pushButton_3, INPUT_PULLUP);
  pinMode (LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("MCU ON-LINE");
  sectionAstatus();
  
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 91110){     // SECTION A01 TRACK 01 ON-LINE
     sectionA01status[0] = 0;// SECTION A01 TRACK 01 STATUS = 0
     sectionAstatus();
  }
  if (data == 91120){     // SECTION A01 TRACK 02 ON-LINE
     sectionA01status[1] = 0;// SECTION A01 TRACK 02 STATUS = 0
     sectionAstatus();
  }
  if (data == 91130){     // SECTION A01 TRACK 03 ON-LINE
     sectionA01status[2] = 0;// SECTION A01 TRACK 03 STATUS = 0
     sectionAstatus();
  }
  if (data == 91111){     // SECTION A01 TRACK 01 OFF-LINE
    sectionA01status[0] = 1;// SECTION A01 TRACK 01 STATUS = 1
    sectionAstatus();
  }
  if (data == 91121){     // SECTION A01 TRACK 02 OFF-LINE
    sectionA01status[1] = 1;// SECTION A01 TRACK 02 STATUS = 1
    sectionAstatus();
  }
  if (data == 91131){     // SECTION A01 TRACK 03 OFF-LINE
    sectionA01status[2] = 1;// SECTION A01 TRACK 03 STATUS = 1
    sectionAstatus();
  }
  if (data == 91213){     // SECTION A02 SENSOR TRACK 01 IMPULSE -> 1213 -> TRACK 01 ON-LINE
    Serial.println(1213);
    sectionA02status[0] = 0;
    sectionA02status[1] = 1;
    sectionA02status[2] = 1;
  }
  if (data == 91223){     // SECTION A02 SENSOR TRACK 02 IMPULSE -> 1223 -> TRACK 02 ON-LINE
    Serial.println(1223);
    sectionA02status[0] = 1;
    sectionA02status[1] = 0;
    sectionA02status[2] = 1;
  }
  if (data == 91233){     // SECTION A02 SENSOR TRACK 03 IMPULSE -> 1233 -> TRACK 03 ON-LINE
    Serial.println(1233);
    sectionA02status[0] = 1;
    sectionA02status[1] = 1;
    sectionA02status[2] = 0;
  }

} // end void TxRxData()

void sectionAstatus(){          // SECTION A01 & A02 STATUS
  Serial.print("SECTION A01 STATUS | ");
  Serial.print(sectionA01status[0]);
  Serial.print(" | ");
  Serial.print(sectionA01status[1]);
  Serial.print(" | ");
  Serial.println(sectionA01status[2]);
  Serial.print("SECTION A02 STATUS | ");
  Serial.print(sectionA02status[0]);
  Serial.print(" | ");
  Serial.print(sectionA02status[1]);
  Serial.print(" | ");
  Serial.println(sectionA02status[2]);
} // end void sectionAstatus()

void MCUautoWork(){             // MCU AUTO WORK
  switch(sectionA01status[0]){
    case 0:
      switch(sectionA01status[2]){
        case 0:
          if (sectionA01status[1] == 1 && sectionA02status[1] == 0){}
          break;
        case 1:
          if (sectionA02status[0] == 1 && sectionA02status[2] == 0){}
          if (sectionA01status[1] == 1 && sectionA02status[1] == 0){}
          break;
      } // end sectionA01status[2]
      Serial.println(1013);
      break;
    case 1:
      switch(sectionA01status[1]){
        case 0:
          if (sectionA01status[2] == 1 && sectionA02status[1] == 1){Serial.println(1023);}
          break;
        case 1:
          switch(sectionA01status[2]){
            case 0:
              if (sectionA02status[1] == 0){Serial.println(1033);}
              break;
            case 1:
              Serial.println("SECTION A OFF-LINE");
              break;
          } // end sectionA01status[2]
          break;
      } // end sectionA01status[1]
      if (sectionA01status[2] == 0 && sectionA02status[0] == 0 && sectionA02status[2] == 1){
        Serial.println(1033);
      }
      break;
  } // end sectionA01status[0]

} // end void MCUautoWork()

void sensorLow() {              // MCU SENSORS WORK
  if (isSensorLow(pushButton_1)){     // PUSHBUTTON 1 IMPULSE 1013
    delay(500);
    Serial.println(1013);
    sectionA02status[0] = 0;
    sectionA02status[1] = 1;
    sectionA02status[2] = 1;
    sectionAstatus();
  }
  if (isSensorLow(pushButton_2)){     // PUSHBUTTON 2 IMPULSE 1023
    delay(500);
    Serial.println(1023);
    sectionA02status[0] = 1;
    sectionA02status[1] = 0;
    sectionA02status[2] = 1;
    sectionAstatus();    
  }
  if (isSensorLow(pushButton_3)){     // PUSHBUTTON 3 IMPULSE 1033
    delay(500);
    Serial.println(1033);
    sectionA02status[0] = 1;
    sectionA02status[1] = 1;
    sectionA02status[2] = 0;
    sectionAstatus();
  }
  if (isSensorLow(sensorMCU01)){
    delay(500);
    MCUautoWork();
  }
} // end void sensorLow()

void loop() {                   // WORK IN LOOP
  if (Serial.available() > 0) TxRxData(); // EXECUTE void TxRxData()
  if (                                    // EXECUTE void sensorLow()
      isSensorLow(pushButton_1) ||
      isSensorLow(pushButton_2) ||
      isSensorLow(pushButton_3) ||
      isSensorLow(sensorMCU01)
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
