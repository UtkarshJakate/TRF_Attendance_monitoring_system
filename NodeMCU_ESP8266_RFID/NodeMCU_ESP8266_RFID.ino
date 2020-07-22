#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
const char* ssid = "NETGEAR27-2.4GHz";                      // Your wifi Name
const char* password = "RoBoCoN_ViT2019";              // Your wifi Password

const char *host = "api.pushingbox.com";                  // pushingbox Host


#define SS_PIN D4  //D2
#define RST_PIN D3 //D1


/**********************
 * Amogh : 64 E9 D1 79
 * Chinmay : 5C 75 19 79
 * Sumedh : 95 A5 16 79
 * Anshul : 7A 0D A7 49
 * Shruti : A0 EF 8A 7C 
 ***********************/
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String Name[6] = {"Utkarsh","Amogh","Chinmay","Sumedh","Anshul","Shruti"};
//                    0         1        2        3         4       5
String Person = "";
void setup() {
  // put your setup code here, to run once:
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);                           // Initialize the Led_OnBoard pin as an output
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);                                    // Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);                                    // This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);                             // Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Successfully Connecting");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());                           //IP address assigned to your ESP

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("RFID Connected");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);

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
  Serial.print(" UID tag :");
  String content= "";
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
  if (content.substring(1) == "32 F2 B8 1E") //change UID of the card that you want to give access
  {
    //Utkarsh
    Serial.println(" Access Granted ");
    Person = Name[0];   
    Serial.println(Person);
    Serial.println();
    Wifi();
  }
  else if(content.substring(1) == "64 E9 D1 79")
  {
    //Amogh
    Serial.println(" Access Granted ");
    Person = Name[1];
    Serial.println(Person);
    Serial.println();
    Wifi();
  }
  else if(content.substring(1) == "5C 75 19 79")
  {
    //Chinmay
    Serial.println(" Access Granted ");
    Person = Name[2];
    Serial.println(Person);
    Serial.println();
    Wifi();
  }
  else if(content.substring(1) == "95 A5 16 79")
  {
    //Sumedh
    Serial.println(" Access Granted ");
    Person = Name[3];
    Serial.println(Person);
    Serial.println();
    Wifi();
  }
  else if(content.substring(1) == "7A 0D A7 49")
  {
    //Anshul
    Serial.println(" Access Granted ");
    Person = Name[4];
    Serial.println(Person);
    Serial.println();
    Wifi();
  }
  else if(content.substring(1) == "A0 EF 8A 7C")
  {
    //Shruti
    Serial.println(" Access Granted ");
    Person = Name[5];
    Serial.println(Person);
    Serial.println();
    Wifi();
  }
  else   {
    Serial.println(" Access Denied ");
    delay(300);
  }
}
void Wifi()
{
  //WIFI connect
    Serial.println("");
    Serial.println("----------------------------------------------");
    Serial.print("connecting to ");
    Serial.println(host);


    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort))
    {
      Serial.println("connection failed");
      return;
    }

    // We now create a URI for the request
    String url = "/pushingbox?";
    url += "devid=v6B970307E814F54";
    url += "";
    url += "&LDR=" + Person;

    //Serial.print("Requesting URL: ");
    //Serial.println(url);
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
      if (millis() - timeout > 4000)
      {
        //Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    {
      String line = client.readStringUntil('\r');
      //Serial.print(line);
      //Serial.print("Data Sent!");
    }
    Serial.println("Done");
    Serial.println("closing connection");
    Serial.println("----------------------------------------------");
}
