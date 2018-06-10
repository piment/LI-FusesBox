
#include <SPI.h>
#include <MFRC522.h>
#define redLed 9
#define greenLed A5
#define btnLed A4
<<<<<<< HEAD
#define relay 4

volatile bool state = false;
=======
#define button 2
#define relay 10

>>>>>>> dbbb3c8cf8bf63375781f5723e9455651a5353c1
const byte readersNb = 8;
const byte RST_PIN = A0;          // Configurable, see typical pin layout above
const byte SS_PIN[8] = {3, 5, 8, A3, A2, A1, 7, 6};         // Configurable, see typical pin layout above
MFRC522 mfrc522[8];  // Create MFRC522 instance

//Fuses ID [215218, 23220, 103218, 10352, 183219, 55219, 752, 231169]
String fuses[8] = {"0", "0", "0", "0", "0", "0", "0", "0"};
bool state = false;

void setup() {
  
  pinMode(2, INPUT_PULLUP);
  pinMode(btnLed, OUTPUT);
  digitalWrite(btnLed, 1);
  
  pinMode(greenLed, OUTPUT);
  digitalWrite(greenLed, 0);
  
  pinMode(redLed, OUTPUT);
  digitalWrite(redLed, 1);
<<<<<<< HEAD
  pinMode(relay, OUTPUT);
  digitalWrite(relay, 0);
=======

  pinMode(relay, OUTPUT);
  digitalWrite(relay, 1);
  
>>>>>>> dbbb3c8cf8bf63375781f5723e9455651a5353c1
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  
  for (uint8_t i = 0; i < 8; i++){
    mfrc522[i].PCD_Init(SS_PIN[i], RST_PIN);    // Init MFRC522
    //mfrc522[i].PCD_SetAntennaGain(mfrc522[i].RxGain_max);
    //mfrc522[i].PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
  }
}

void checkReaders(){
  
  for (int i = 0; i < 8; i++){
    
    // Look for new cards
    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      //Serial.print("Checking Reader N°");
      //Serial.println(i);
      String fuse_id;
      fuse_id += mfrc522[i].uid.uidByte[0];
      fuse_id += mfrc522[i].uid.uidByte[1];
      //Serial.println(fuse_id);
      fuses[i] = fuse_id;
    }
    delay(50);
  }
}

void loop() {
  
<<<<<<< HEAD
  if(digitalRead(2) == 0) {
=======
  
  
  if(digitalRead(button) == 0) {
>>>>>>> dbbb3c8cf8bf63375781f5723e9455651a5353c1
    digitalWrite(btnLed, 0);
    
    for(int i =0; i < 8; i++){
      fuses[i] = "0";
    }
    
    checkReaders();
    delay(100);
    checkReaders();
    
    //Fuses ID seq 1 [183219, 103218, 10352, 215218, 752, 55219, 231169, 23220]
    if(fuses[0] == "183219"){
      if(fuses[1] == "103218"){
        if(fuses[2] == "10352"){
          if(fuses[3] == "215218"){
            if(fuses[4] =="752"){
              if(fuses[5] == "55219"){
                if(fuses[6] == "231169"){
                  if(fuses[7] == "23220"){
                    state = true;
                  }
                  else{
                    state = false;
                  } 
                }
                else{
                  state = false;
                }
              }
              else{
                state = false;
              }
            }
            else{
              state = false;
            }
          }
          else{
            state = false;
          }
        }
        else{
          state = false;
        }
      }
      
      //Fuses ID seq 2 [183219, 23220, 231169, 55219, 752, 215218, 10352, 103218]
      else if(fuses[1] == "23220"){
        if(fuses[2] == "231169"){
          if(fuses[3] == "55219"){
            if(fuses[4] =="752"){
              if(fuses[5] == "215218"){
                if(fuses[6] == "10352"){
                  if(fuses[7] == "103218"){
                    state = true;
                  }
                  else{
                    state = false;
                  }
                }
                else{
                  state = false;
                }
              }
              else{
                state = false;
              }
            }
            else{
              state = false;
            }
          }
          else{
            state = false;
          }
        }
        else{
          state = false;
        }
      }
      else{
        state = false;
      }
    }
<<<<<<< HEAD
    else{
        state = false;
      }
    
    
    
    delay(500);
    digitalWrite(btnLed, 1);
  }
  if(state == false){
      //Serial.println("Seq error");
      digitalWrite(greenLed, 0);
      digitalWrite(redLed, 1);
      //delay(3000);
      //digitalWrite(redLed, 0);
      digitalWrite(relay, 0);
    }
    else{
      digitalWrite(relay, 1);
      digitalWrite(redLed, 0);
      digitalWrite(greenLed, 1);
      //delay(3000);
      //digitalWrite(relay, 0);
      //digitalWrite(greenLed, 0);
    }
  delay(200);
  
=======
    else{
      state = false;
    }
    
  }
 if(state){
      digitalWrite(greenLed, 1);
      digitalWrite(redLed, 0);
      digitalWrite(relay, 0);
 }
 else{
      digitalWrite(greenLed, 0);
      digitalWrite(redLed, 1);
      digitalWrite(relay, 1);
 }
 delay(500);
 digitalWrite(btnLed, 1);
>>>>>>> dbbb3c8cf8bf63375781f5723e9455651a5353c1
    

  
  
}
