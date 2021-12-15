// LEGO_train_track_MCU

#define sensorMCU01     2
#define pushButton_1    4
#define pushButton_2    7
#define pushButton_3    8
int delayIsSensorLow = 20;
long data;
int sectionA01status[3] = {0,0,0};
int sectionA02status[3] = {0,0,0};

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
  
  //SETTINGS
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("MCU ON-LINE");
  sectionAstatus();
  
} //  end void setup()

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
  if (isSensorLow(sensorMCU01)){      // MCU SENSOR 01 IMULSE
    delay(300);
    sectionAstatus();
    MCUautoWork();
    }
} // end void sensorLow()

void sectionAstatus(){          // SECTION A01 & A02 STATUS
  Serial.print("SECTION A01 STATUS | ");
  Serial.print(sectionA01status[0]);
  Serial.print(" | ");
  Serial.print(sectionA01status[1]);
  Serial.print(" | ");
  Serial.print(sectionA01status[2]);
  Serial.println(" |");
  Serial.print("SECTION A02 STATUS | ");
  Serial.print(sectionA02status[0]);
  Serial.print(" | ");
  Serial.print(sectionA02status[1]);
  Serial.print(" | ");
  Serial.print(sectionA02status[2]);
  Serial.println(" |");
} // end void sectionAstatus()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 91113) sectionA01status[0] = 1;   // SECTION A01 SENSOR TRACK 01 IMPULSE
  if (data == 91123) sectionA01status[1] = 1;   // SECTION A01 SENSOR TRACK 02 IMPULSE
  if (data == 91133) sectionA01status[2] = 1;   // SECTION A01 SENSOR TRACK 03 IMPULSE
  if (data == 91110) sectionA01status[0] = 0;   // SECTION A01 TRACK 01 SWITCHED ON-LINE
  if (data == 91120) sectionA01status[1] = 0;   // SECTION A01 TRACK 02 SWITCHED ON-LINE
  if (data == 91130) sectionA01status[2] = 0;   // SECTION A01 TRACK 03 SWITCHED ON-LINE
  if (data == 91210){                           // SECTION A02 TRACK 01 SWITCHED ON-LINE
    Serial.println(1213);                         // SECTION A01 TRACK 01 SWITCH TO ON-LINE
    sectionA02status[0] = 0;                      // SECTION A02 TRACK 01 ON-LINE
    sectionA02status[1] = 1;                      // SECTION A02 TRACK 02 OFF-LINE
    sectionA02status[2] = 1;                      // SECTION A02 TRACK 03 OFF-LINE
    }
  if (data == 91220){                           // SECTION A02 TRACK 02 SWITCHED ON-LINE
    Serial.println(1223);                         // SECTION A01 TRACK 02 SWITCH TO ON-LINE
    sectionA02status[0] = 1;                      // SECTION A02 TRACK 01 OFF-LINE
    sectionA02status[1] = 0;                      // SECTION A02 TRACK 02 ON-LINE
    sectionA02status[2] = 1;                      // SECTION A02 TRACK 03 OFF-LINE
    }
  if (data == 91230){                           // SECTION A02 TRACK 03 SWITCHED ON-LINE
    Serial.println(1233);                         // SECTION A01 TRACK 03 SWITCH TO ON-LINE
    sectionA02status[0] = 1;                      // SECTION A02 TRACK 01 OFF-LINE
    sectionA02status[1] = 1;                      // SECTION A02 TRACK 02 OFF-LINE
    sectionA02status[2] = 0;                      // SECTION A02 TRACK 03 ON-LINE
    }
  
} // end void TxRxData()

void MCUautoWork(){             // MCU AUTO WORK

  switch(sectionA01status[0]){
    case 0:
      if (sectionA01status[1] == 0 && sectionA01status[2] == 1)Serial.println(1213);
      if (sectionA01status[1] == 1 && sectionA01status[2] == 0)Serial.println(1213);
      break;
    case 1:
      if (sectionA01status[1] == 0 && sectionA01status[2] == 1) Serial.println(1223);
      if (sectionA01status[1] == 0 && sectionA01status[2] == 0) Serial.println(1233);
      if (sectionA01status[1] == 1 && sectionA01status[2] == 0) Serial.println(1233);
      break;
    }
  
} // end void MCUautoWork()

void loop() {                   // WORK IN LOOP
  
    // EXECUTE void TxRxData()
  if (Serial.available() > 0) TxRxData();
    // EXECUTE void sensorLow()
  if (isSensorLow(pushButton_1) || isSensorLow(pushButton_2) || isSensorLow(pushButton_3) || isSensorLow(sensorMCU01)) sensorLow();

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
