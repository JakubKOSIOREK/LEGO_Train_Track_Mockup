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
  Serial.println(90000);
  delay(5000);
  Serial.println(1020);   //TOR 2 servoL na wprost, servoP na wprost


  //INPUTS
  pinMode (pushButton_1, INPUT_PULLUP);
  pinMode (pushButton_2, INPUT_PULLUP);
  pinMode (pushButton_3, INPUT_PULLUP);
      
} //  end void setup()

void TxRxData(){                // TRANSMISJA DANYCH PO UART
  
  data = Serial.parseInt();
  delay(10);

  //***GDY ODPOWIEDŹ Z SEKCJI A***//
  
  if (data == 91010){   // TOR 1 ON-LINE

  }

  if (data == 91020){   // TOR 2 ON-LINE

  }

  if (data == 91030){   // TOR 3 ON-LINE
    Serial.println(1031);
  }

  if (data == 91012){   // SEMAFOR 1 CZERWONY

  }

  if (data == 91022){   // SEMAFOR 2 CZERWONY

  }

  if (data == 91032){   // SEMAFOR 3 CZERWONY

  }


  //***GDY ODPOWIEDŹ Z SEKCJI B***//
  
  if (data == 92011){   //SEMAFOR 1 NA ZIELONY
    Serial.println(2011);
  }
  
  if (data == 92012){   //SEMAFOR 2 NA ZIELONY
    Serial.println(2012);
    delay(500);
  }

  if (data == 92013){   //SEMAFOR 3 NA ZIELONY
    Serial.println(2013);
    delay(500);
  }

} // end void TxRxData()


void loop() {                   // WORK IN LOOP

  if(Serial.available() > 0) TxRxData(); //PRZEJŚCIE DO FUNKCJI void TxRxData()
  
  if (digitalRead(pushButton_1)==LOW){  //TOR 1
      delay(500);
      Serial.println(1010);
      }else{
  }

  if (digitalRead(pushButton_2)==LOW){ //TOR 2
      delay(500);
      Serial.println(1020);
      }else{
  }

  if (digitalRead(pushButton_3)==LOW){ //TOR 3
      delay(500);
      Serial.println(1030);
      }else{
  }


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
