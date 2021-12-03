// LEGO_train_track_MCU


//SENSORS

#define sensorSectionA  12
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
  pinMode (sensorSectionA, INPUT_PULLUP);
  pinMode (pushButton_1, INPUT_PULLUP);
  pinMode (pushButton_2, INPUT_PULLUP);
  pinMode (pushButton_3, INPUT_PULLUP);
      
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

  if (data == 2013){     // SECTION B sensorTrack1 -> is SECTION A SEMAPHOR TRACK 1 GREEN ON & RED OFF -> 82012
    Serial.println(81012);
  }

  if (data == 2023){     // SECTION B sensorTrack2 -> is SECTION A SEMAPHOR TRACK 2 GREEN ON & RED OFF -> 82022
    Serial.println(81022);
  }

  if (data == 2033){     // SECTION B sensorTrack3 -> is SECTION A SEMAPHOR TRACK 3 GREEN ON & RED OFF -> 82032
    Serial.println(81032);
  }


  if (data == 10120){ // TRACK 1 to ON-LINE -> 1014
    Serial.println(1014);
  }

  if (data == 10220){ // TRACK 2 to ON-LINE -> 1024
    Serial.println(1024);
  }

  if (data == 10320){ // TRACK 3 to ON-LINE -> 1034
    Serial.println(1034);
  }



} // end void TxRxData()


void loop() {                   // WORK IN LOOP

  if(Serial.available() > 0) TxRxData(); // EXECUTE void TxRxData()

  if (digitalRead(sensorSectionA)==LOW){ // SENSOR A           IMPULSE 1003
      delay(500);
      Serial.println(1003);
      }else{
  } // end sensorSectionA == LOW
  
  if (digitalRead(pushButton_1)==LOW){   // PUSHBUTTON TRACK 1 IMPULSE 1013
      delay(500);
      Serial.println(1013);
      }else{
  } // end pushButton_1 == LOW

  if (digitalRead(pushButton_2)==LOW){   // PUSHBUTTON TRACK 2 IMPULSE 1023
      delay(500);
      Serial.println(1023);
      }else{
  } // end pushButton_2 == LOW

  if (digitalRead(pushButton_3)==LOW){   // PUSHBUTTON TRACK 3 IMPULSE 1033
      delay(500);
      Serial.println(1033);
      }else{
  } // end pushButton_3 == LOW

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
