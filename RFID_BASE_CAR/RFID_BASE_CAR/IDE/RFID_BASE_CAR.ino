#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define RFID_SCK 13
#define RFID_MOSI 11
#define RFID_MISO 12
#define MINIMUM_TIME_BETWEEN_CARDS 0000
//Motor A
const int inputPin1  = 5;    
const int inputPin2  = 6;    
//Motor B
const int inputPin3  = 10;  
const int inputPin4  = 8;  
MFRC522 mfrc522(SS_PIN, RST_PIN);
long int last_card_read;
int Value[4]={0000, 0000, 0000, 0000};
char* CardID[4]={“87 44 65 62”, “79 25 93 99”, “B9 09 CC 99”, “F3 70 9F 1B”};  // These Line Show Error fetch card uid and write here.
void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
{
    pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
    pinMode(inputPin3, OUTPUT);
    pinMode(inputPin4, OUTPUT);  
}


}
void loop()
{
if(millis() – last_card_read >= MINIMUM_TIME_BETWEEN_CARDS){
 // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
 //Show UID on serial monitor
  Serial.print(“UID tag :”);
  String content= “”;
  byte letter;


  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? ” 0″ : ” “);
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? ” 0″ : ” “));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  content = content.substring(1);
  //go through all of the CardIDs in the array and check if it matches with scanned one
  #define COMMANDS_LENGTH 4
  for(int a = 0; a < COMMANDS_LENGTH; a++)
  {
    last_card_read = millis();
    if(content == CardID[a])
    {
      if(CardID[a] == “87 44 65 62”)
      {
    digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH);
    delay(Value[a]);
   }
    else if(CardID[a] == “79 25 93 99”)
      {
    digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, HIGH);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH);
    delay(1000);


     digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH);
    delay(Value[a]);
   }
    else if(CardID[a] == “B9 09 CC 99”)
      {
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, HIGH);
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW);
     delay(Value[a]);
     }
     else if(CardID[a] == “F3 70 9F 1B”)
      {
    digitalWrite(inputPin1, LOW);


    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, LOW);
     delay(Value[a]);
     }
  }
}
}
}
