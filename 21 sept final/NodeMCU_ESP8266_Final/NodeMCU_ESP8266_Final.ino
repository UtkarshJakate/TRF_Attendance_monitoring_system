#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;
void getTime();

char mystr[20]; //Initialized variable to store recieved data
String D;
String Data[6] = {"32 F2 B8 1E","64 E9 D1 79","5C 75 19 79","95 A5 16 79","7A 0D A7 49","A0 EF 8A 7C"};
String Name[6] = {"Utkarsh", "Amogh", "Chinmay", "Sumedh", "Anshul", "Shruti"};
//                    0         1        2        3         4       5
//String Person = "";

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  Serial.readBytesUntil('\0',mystr,12); //Read the serial data and store in var
  //Serial.println(mystr); //Print data on Serial Monitor
  delay(1000);
  charToString(mystr,D);
  Serial.println(D);
  for( int i = 0; i < 6; i++)
  {
    if (D == Data[i])
    {
      Serial.println("Access Granted");
      Serial.println(Name[i]);
      delay(300);
      getTime();
      break;
    }
  }
}

void charToString(const char S[], String &D)
{
    byte at = 0;
    const char *p = S;
    D = "";
    while (*p++) {
      D.concat(S[at++]);
      }
}

void getTime()
{
  DateTime now = RTC.now();
  String Date = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
  Serial.println(Date);
  String Time = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  Serial.println(Time);
}
