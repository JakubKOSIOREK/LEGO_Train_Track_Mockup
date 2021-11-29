// LEGO_train_track_MCU


//SENSORS

#define pushButton_1  4
#define pushButton_2  7
#define pushButton_3  8


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
      
} //  end void setup()

void TxRxData(){                // TxRxData TRANSMISION
  
  data = Serial.parseInt();
  delay(10);

//***SECTION A RECEIVED DATA***//

  if (data == 91001){ // SECTION A OFF-LINE
    
  }

  if (data == 91002){ // SECTION A ON-LINE
    
  }

//***SECTION B RECEIVED DATA***//

  if (data == 92013){     // SENSOR TRACK 1 0013
    Serial.println(0013);
  }

  if (data == 92023){     // SENSOR TRACK 2 0023
    Serial.println(0023);
  }

  if (data == 92033){     // SENSOR TRACK 3 0033
    Serial.println(0033);
  }

} // end void TxRxData()


void loop() {                   // WORK IN LOOP

  if(Serial.available() > 0) TxRxData(); // EXECUTE void TxRxData()
  
  if (digitalRead(pushButton_1)==LOW){   // PUSHBUTTON TRACK 1 IMPULSE 0013
      delay(500);
      Serial.println(0013);
      }else{
  } // end pushButton_1 == LOW

  if (digitalRead(pushButton_2)==LOW){   // PUSHBUTTON TRACK 2 IMPULSE 0023
      delay(500);
      Serial.println(0023);
      }else{
  } // end pushButton_2 == LOW

  if (digitalRead(pushButton_3)==LOW){   // PUSHBUTTON TRACK 3 IMPULSE 0033
      delay(500);
      Serial.println(0033);
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
