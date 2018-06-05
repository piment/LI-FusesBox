
#include <SPI.h>
#include <MFRC522.h>
const byte readersNb = 8;
const byte RST_PIN = A0;          // Configurable, see typical pin layout above
const byte SS_PIN[8] = {4, 5, A7, A6, A3, A2, A1, 6};         // Configurable, see typical pin layout above

MFRC522 mfrc522[8];  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  for (uint8_t i = 0; i < 8; i++){
    mfrc522[i].PCD_Init(SS_PIN[i], RST_PIN);    // Init MFRC522
    mfrc522[i].PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
  }
  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  for (int i = 0; i < 8; i++){
    
    // Look for new cards
    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      Serial.print("Checking Reader N°");
      Serial.println(i);
      unsigned int hex_num;
      hex_num = mfrc522[i].uid.uidByte[0] << 24;
      hex_num += mfrc522[i].uid.uidByte[1] << 16;
      hex_num += mfrc522[i].uid.uidByte[2] << 8;
      hex_num += mfrc522[i].uid.uidByte[3];
      Serial.println((int)hex_num);
    }
    

  }
  
}
