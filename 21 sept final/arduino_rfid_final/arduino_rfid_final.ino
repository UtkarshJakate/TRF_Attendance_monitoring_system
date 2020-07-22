/*
    Created by TheCircuit
*/

//Amogh : 64 E9 D1 79
//Chinmay : 5C 75 19 79
//Sumedh : 95 A5 16 79
//Anshul : 7A 0D A7 49
//Shruti : A0 EF 8A 7C
#define SS_PIN 4  //D2
#define RST_PIN 7 //D1

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
char s[12];

const int rs = 9, en = 8, d4 = 5, d5 = 10, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial Ms(A0, A1); //Rx Tx
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String Name[6] = {"Utkarsh", "Amogh", "Chinmay", "Sumedh", "Anshul", "Shruti"};
//                    0         1        2        3         4       5
String Person = "";
String Key = "";
int flag = 0;
void setup()
{
  Ms.begin(9600);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Connected");
  lcd.begin(16, 2);
}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
     flag = 1;
     return;
  }
  else
  {
    flag = 0;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  /*
    Key = content.substring(1);
    for(int i = 0; i < 11; i++)
    {
    Ms.write(Key[i]);
    }
  */
  Key = content.substring(1);
  Key.toCharArray(s,12);
  if(flag == 0)
  {
    Ms.write(s,12);
  }
  else
  {
    Ms.write("No");  
  }
  if (content.substring(1) == "32 F2 B8 1E") //change UID of the card that you want to give access
  {
    //Utkarsh
    Serial.println(" Access Granted ");
    Person = Name[0];
    Serial.println(Person);
    lcd.print(Person);
    Serial.println();
    /*if(Ms.available()>0)
    {
    Ms.flush();
    Ms.write("Hello");
    Serial.println("Done");
    }*/
    delay(300);
  }
  else   {
    Serial.println(" Access Denied ");
    delay(300);
  }
  lcd.clear();
}
