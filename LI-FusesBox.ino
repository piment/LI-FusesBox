
#include <SPI.h>
#include <MFRC522.h>
const byte readersNb = 8;
const byte RST_PIN = A0;          // Configurable, see typical pin layout above
const byte SS_PIN[8] = {3, 5, 8, A3, A2, A1, 7, 6};         // Configurable, see typical pin layout above
//Fuses ID [215218, 23220, 103218, 10352, 183219, 55219, 752, 231169]
String fuses[8] = {"0", "0", "0", "0", "0", "0", "0", "0"};
MFRC522 mfrc522[8];  // Create MFRC522 instance

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  for (uint8_t i = 0; i < 8; i++){
    mfrc522[i].PCD_Init(SS_PIN[i], RST_PIN);    // Init MFRC522
    //mfrc522[i].PCD_SetAntennaGain(mfrc522[i].RxGain_max);
    mfrc522[i].PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
  }
  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
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
  
  if(digitalRead(2) == 0) {
    //Serial.println("button pushed");
    for(int i =0; i < 8; i++){
      fuses[i] = "0";
    }
    checkReaders();
    delay(100);
    checkReaders();
    Serial.print("[");
    for(int i = 0; i < 8; i++){
      
      Serial.print(fuses[i]);
      if(i == 7){
        Serial.println("]"); 
      }
      else {
        Serial.print(", ");
      }
    }
    //Fuses ID seq 1 [183219, 103218, 10352, 215218, 752, 55219, 231169, 23220]
    //Fuses ID seq 2 [183219, 23220, 231169, 55219, 752, 215218, 10352, 103218]
    if(fuses[0] == "183219"){
      if(fuses[1] == "103218"){
        if(fuses[2] == "10352"){
          if(fuses[3] == "215218"){
            if(fuses[4] =="752"){
              if(fuses[5] == "55219"){
                if(fuses[6] == "231169"){
                  if(fuses[7] == "23220"){
                    Serial.println("Seq 01 OK");
                  }
                }
              }
            }
          }
        }
      }
      else if(fuses[1] == "23220"){
        if(fuses[2] == "231169"){
          if(fuses[3] == "55219"){
            if(fuses[4] =="752"){
              if(fuses[5] == "215218"){
                if(fuses[6] == "10352"){
                  if(fuses[7] == "103218"){
                    Serial.println("Seq 02 OK");
                  }
                }
              }
            }
          }
        }
      }
    }
    else{
      Serial.println("Seq error");
    }
    delay(500);
  }
  delay(200);
    

  
  
}
