#include <SPI.h>
#include <SD.h>

String str = "32 F2 B8 1E",sd;
char ch[12];
File file;
char c;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Initializing SD card...");
  int i = 0, j = 0;
  if (!SD.begin(D4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
    file = SD.open("Compare.txt",FILE_READ);
  if(file)
  {
    //Serial.println("Compare.txt");
    while(file.available())
    {
      c = char(file.read());
      
      if(c == '\n' && j == 5)
      {
        break;
      }
      if(c == '\n')
      {
        j++;
      }
      if(j<4)
      {
        continue;
      }
      if(i < 11)
      {
        ch[i] = c;
        i++;
      }
      Serial.print(c);
    }
    charToString(ch,sd);
    file.close();
    if(sd == str)
    {
      Serial.println("Hawa");
    }
  }  
  else
  {
    Serial.println("Error Opening File");
  }
}
void loop() {
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
