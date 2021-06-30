
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Set these to run example.
#define SS_PIN D4  //D2
#define RST_PIN D0 //D1
#define FIREBASE_HOST "gestion-absence-cdb21-default-rtdb.firebaseio.com" //https://wemos4firebase.firebaseio.com/
#define FIREBASE_AUTH "AKs7Eh4GolvUHym7ExQFM0QZZnGjHUzoGSIzK8tw"
#define WIFI_SSID "ESP1"
#define WIFI_PASSWORD "12345678"


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance/object.
int variable = 0;
 
void setup() {
 
Serial.begin(9600);   // Initiate a serial communication
SPI.begin();      // Initiate  SPI bus
mfrc522.PCD_Init();   // Initiate MFRC522
Serial.println("Show your card:");
 

 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
   
}
 
 
 
 
 
void loop() {
 int n = 0;
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
Serial.println();
String content= "";
byte letter;
content =printString(mfrc522.uid.uidByte, mfrc522.uid.size);

Firebase.pushString("ID",content);
  //Serial.print("pushed: /logs/(mfrc522.uid.uidByte[s])");
  

 
 
  if (Firebase.failed()) {
      Serial.print("setting /number2 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number1 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
 
  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);
 
  // remove value
  Firebase.remove("number");
  delay(1000);
 
  // set string value
  Firebase.setString("message", "hello world");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
 
  // append a new value to /logs
 
  // handle error

 
  delay(1000);
 
}

void printDec(byte *buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {

   Serial.print(buffer[i] < 0x10 ? " 0" : " ");
   Serial.print(buffer[i], DEC);
   
 }
 }
 String printString(byte *buffer, byte bufferSize) {
  String rfid_uid = "";
  for (byte i = 0; i < bufferSize; i++) {
    String uid_part = String(buffer[i], HEX); 
        Serial.print(uid_part);
        rfid_uid += uid_part;
  }
  return rfid_uid;
 }
 














////////////////////////////////////////////////////////////

 client.println("Ana hna");
 // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
 if ( ! rfid.PICC_IsNewCardPresent())
   return;
 // Verify if the NUID has been readed
 if ( ! rfid.PICC_ReadCardSerial())
   return;
/////////////////esp