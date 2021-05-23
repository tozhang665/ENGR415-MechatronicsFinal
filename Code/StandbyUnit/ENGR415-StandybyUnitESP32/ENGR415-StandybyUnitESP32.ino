//This code is to be uploaded to the ESP32.
// This code receives data from the Arduino Mega onto the ESP32, and sends it to the MQTT Server.


#include <WiFi.h>
#include <PubSubClient.h>

#define RXD2 16    //ESP32 UART2 pins
#define TXD2 17

//#define RXD0 1
//#define TXD0 3


// Add Wi-Fi and server settings
const char* ssid ="Luckys Territory";
const char* pass= "unevenpond977";
const char* brokerUser= ("Standby");
const char* brokerPass= ("Standby");
const char* broker= ("broker.emqx.io");
const char* outTopic = ("ENGRtest");
const char* inTopic= ("ENGRtest");

WiFiClient espClient;
PubSubClient client(espClient);


char messages[100];
String MegaData;

void setupwifi()
{
  delay(100);
  Serial.println("\nConnecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print("-");
  }
  Serial.print("\nConnected to");
  Serial.println(ssid);
}

void reconnect(){
  while(!client.connected())
  {
    Serial.print("\nConnecting to");
    Serial.println(broker);
    if(client.connect("Student2", brokerUser, brokerPass)){  // Add client ID or Name
      Serial.println("\nConnected to");
      Serial.println(broker);
      client.subscribe(inTopic);
    }else{
      Serial.println("\nTrying connect again");
      delay(5000);
    }
    }
  }



  void callback(char* topic, byte* payload, unsigned int length){
  String messageout= "";
  for(int i=0; i<length; i++){
  ((char) payload[i]);
    Serial.print((char) payload[i]);
    messageout+=(char) payload[i];
    if(Serial1.available()){    //Checks if Arduino Mega UART1 is available
      if(messageout == "UpA"){   //If the server output matches the string, it sends a string to the Arduino Mega UART1
      Serial1.println("UpA");
      Serial.println("Go Left");
      }
      if(messageout == "DownA"){
      Serial1.println("DownA");
      Serial.println("Go Right");
      }
      if(messageout == "UpB"){
      Serial1.println("UpB");
      Serial.println("Go Up Bitch");
      }
      if(messageout == "DownB"){
      Serial1.println("DownB");
      Serial.println("Go Down");
      }
      if(messageout == "LEDs off"){
      Serial1.println("All Off");
      }
    }
   Serial.print("Message contains: ");
   Serial.println(messageout);
   Serial.println();
  }
}
  
  
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // ESP32 UART 2 pins
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2); //Mega UART 1 pins
  setupwifi();
  client.setServer(broker, 1883);
  client.setCallback(callback);
}

void loop() 
{

  if (!client.connected()){
    reconnect();
  }
  client.loop();
  
  if(Serial2.available()){      // This portion of the code reads the Arduino Mega serial monitor output through the ESP32 UART2 pins. It then sends the data to the MQTT server.
   String MegaData=Serial2.readString();  // Changes the string to a char and publishes to the server.
   MegaData.toCharArray(messages,10);
   client.publish(outTopic,messages);
   delay(500); 
  }
  
}
  

 
