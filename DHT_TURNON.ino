#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

// DHT SensorPIN SETTING
#define pumpPin 4
// WIFI SETTINGS
const char *ssid = "Jan router5RysowałTrójkąty";
const char *password = "";
//SCKETIO SETTINGS
const char *socketServer = "onandon2.herokuapp.com";
//const int socketPort = 5000;
SocketIoClient socket;


void togglePump(const char *payload, size_t length)
{
  char subs[5];
  memcpy(subs, &payload[9], 4);
  subs[4] = '\0';
  
  Serial.printf("PUMP status: %s\n", subs);
  if(strcmp(subs,"true") == 0) {
    digitalWrite(pumpPin, HIGH);
  } else {
    digitalWrite(pumpPin, LOW);
  }
}

void setup() {
  Serial.begin(115200); //SERIAL PORT INICIALIZATION
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //WIFI CONFIG/RESET
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);//CONNECT TO WIFI

  while (WiFi.status() != WL_CONNECTED) //WAITING FOR CONNECTED
  {
    delay(100);
    Serial.print(".");
  }  
  
///CONNECT WITH SERVER
  socket.begin(socketServer);
  socket.on("pump", togglePump);

}


void loop() {
    socket.loop();
}
