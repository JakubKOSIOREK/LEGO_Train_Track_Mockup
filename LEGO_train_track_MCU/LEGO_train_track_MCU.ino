// LEGO_train_track_MCU


//SENSORS

#define sensorToSectionA 2
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
  Serial.println("MCU ON-LINE");
  
  //INPUTS
  pinMode (sensorToSectionA, INPUT_PULLUP);
  pinMode (pushButton_1, INPUT_PULLUP);
  pinMode (pushButton_2, INPUT_PULLUP);
  pinMode (pushButton_3, INPUT_PULLUP);
  pinMode (LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
      
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 2013){     // SECTION B sensorTrack1 -> is SECTION A SEMAPHOR TRACK 1 RED ON -> 81011
    Serial.println(81011);
  }

  if (data == 2023){     // SECTION B sensorTrack2 -> is SECTION A SEMAPHOR TRACK 2 RED ON -> 81021
    Serial.println(81021);
  }

  if (data == 2033){     // SECTION B sensorTrack3 -> is SECTION A SEMAPHOR TRACK 3 RED ON -> 81031
    Serial.println(81031);
  }


  if (data == 10111){    // TRACK 1 to ON-LINE -> 1014
    Serial.println(1014);
  }

  if (data == 10211){    // TRACK 2 to ON-LINE -> 1024
    Serial.println(1024);
  }

  if (data == 10311){    // TRACK 3 to ON-LINE -> 1034
    Serial.println(1034);
  }

} // end void TxRxData()


void sectionMCUwork() {           // SEKTION MCU WORK

  if (isSensorLow(sensorToSectionA)){ // SENSOR MCU       IMPULSE 1003
      delay(500);
      Serial.println(1003);
  } // end 1003

  if (isSensorLow(pushButton_1)){     // PUSHBUTTON 1     IMPULSE 1013
      delay(500);
      Serial.println(1013);
  } // end 1013

  if (isSensorLow(pushButton_2)){     // PUSHBUTTON 2     IMPULSE 1023
      delay(500);
      Serial.println(1023);
  } // end 1023

  if (isSensorLow(pushButton_3)){     // PUSHBUTTON 3     IMPULSE 1033
      delay(500);
      Serial.println(1033);
  } // end 1033

} // end sectionMCUwork()


void loop() {                   // WORK IN LOOP

  // EXECUTE void TxRxData()
  if (Serial.available() > 0) TxRxData();

  // EXECUTE void sectionAwork()
  if (isSensorLow(sensorToSectionA) || isSensorLow(pushButton_1) || isSensorLow(pushButton_2) || isSensorLow(pushButton_3)) sectionMCUwork();

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
