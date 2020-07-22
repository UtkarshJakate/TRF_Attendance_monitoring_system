#include <ESP8266WiFi.h>
                                // Initialize the Led_OnBoard 
int button = D0;                                           // Initialize Push button 

const char* ssid = "Hindustani bhau 2.4";                      // Your wifi Name       
const char* password = "mtlbmeralavda@24$terimeri";              // Your wifi Password

const char *host = "api.pushingbox.com";                  // pushingbox Host

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  
  pinMode(LED_BUILTIN, OUTPUT);                           // Initialize the Led_OnBoard pin as an output
  pinMode(button, INPUT_PULLUP);                          // initialize the pushbutton pin as an input
  
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);                                    // Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);                                    // This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);                             // Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
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
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  
  String Button_status = "";
  if (digitalRead(button) == LOW) {
  Button_status = "Button_pressed"; 
  }
  else{
  Button_status = "Button_not_pressed";  
  }
  
  int ldrvalue=analogRead(A0);                              //Read Analog value of LDR
  String LdrValueSend = String(ldrvalue);                   //interger to String conversion

  Serial.println("");
  Serial.println("----------------------------------------------");
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/pushingbox?";
  url += "devid=v6B970307E814F54";
  url += "";
  url += "&LDR="+LdrValueSend;
  url += "&Button="+Button_status;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 4000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    Serial.print("Data Sent!");
  }
  
  Serial.println();
  Serial.println("closing connection");
  Serial.println("----------------------------------------------");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
}
