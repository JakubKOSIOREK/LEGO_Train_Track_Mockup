// LEGO_train_track_MCU

//BIBLIOTEKI


//SEMAFORY


//CZUJNIKI
#define sensor_Tor1  2
#define sensor_Tor2  3
#define sensor_Tor3  4

//SERVA


//ZMIENNE
int delayIsSensorLow = 20;
int data;



//ZEGAR
unsigned long czas;


//USTAWIENIA POCZĄTKOWE LEGO_train_track_MCU
void setup() {

  //COMM
  Serial.begin(38400);
  delay(1000);
  Serial.println(92000);
  
  //OUTPUTS


  //INPUTS


  //SETTINGS

    
} //  end void setup()

void TxRxData(){
  
  data = Serial.parseInt();
  delay(10);



  
} // end void TxRxData()


void loop() {



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
