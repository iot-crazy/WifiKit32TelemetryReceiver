#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Timer.h>

// WiFi network name and password:
char WifiName[] = "SET YOU WIFI SSID NAME HERE";
char WifiPassword[] = "SET YOUR WIFI PASSWORD HERE";

//  a timer to call things at intervals
Timer t;

WiFiUDP sock;
char incomingPacket[255];  // buffer for incoming packets
const int udpPort = 49090; // The UDP port to listen for notifications
char* lastWifiStatus = "";

//Initialise the Screen
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 15, /* data=*/ 4);   // ESP32 Thing, HW I2C with pin remapping

char * getWifiStatus()
{
  switch (WiFi.status()) {
  case     WL_IDLE_STATUS:
    return "Idle";
    break;
  case  WL_NO_SSID_AVAIL:
    return "No SSID Avail";
    break;
  case WL_SCAN_COMPLETED:
    return "Scan compl";
    break;
  case WL_CONNECTED:
    return "Connected";
    break;
  case WL_CONNECT_FAILED:
    return "Failed";
    break;
  case WL_CONNECTION_LOST:
    return "Conn Lost";
    break;
  case WL_DISCONNECTED:
    return "Disconnect";
    break;
  }
  return "Unknown";
}

/* Connect to the WiFi */
void connectWifi()
{
  Serial.println("Connecting wifi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WifiName, WifiPassword);
}

/* Act upon WiFi events */
void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event) {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.println("Wifi Connected");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.subnetMask());
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("Wifi disconncted");
      delay(5000);
      connectWifi();
    break;
  }
}



/* prepare the screen */
void u8g2_prepare(void) {
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

/* draw telemetry values to the screen */
void drawTelem(float temperature, float humidity, float pressure)
{
  char tbuffer[25], hbuffer[25];
  sprintf (tbuffer, "%.2f%cC", temperature, 0xb0);
  sprintf (hbuffer, "%.2f%%", humidity);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_fub25_tf); 
  u8g2.drawStr(0, 0, tbuffer);
  u8g2.drawStr(0, 29, hbuffer);
  u8g2.setFont(u8g2_font_6x10_tf); 
  u8g2.drawStr(0, 56, getWifiStatus());
  u8g2.sendBuffer();
}

void receiveTelem()
{
  Serial.print(".");
  int packetSize = sock.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, sock.remoteIP().toString().c_str(), sock.remotePort());
    int len = sock.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

  // attempt to parse
  float dataref[3] = {0.0};
  for (int i=0; i<3; i++){
    Serial.println(i);
    if (packetSize >= 5 + (sizeof(float) * i)) {
      memcpy(&dataref[i], incomingPacket + 5 + (sizeof(float) * i), sizeof(float));
      if (dataref[i] < 0)
      {
        dataref[i] = 0;
      }
    }
  }

  Serial.printf("Temp: %.2f C \n", dataref[0]);
  Serial.printf("Humid: %.2f % \n", dataref[1]);
  Serial.printf("Pres: %.2f Pa\n", dataref[2]);
  Serial.println();

  drawTelem(dataref[0], dataref[1], dataref[2]);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  u8g2.begin();
  u8g2_prepare();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf); 
  u8g2.drawStr(0, 1, "Starting WiFi ");
  u8g2.sendBuffer();

  WiFi.onEvent(WiFiEvent);
  connectWifi();
  delay(500);

  sock.begin(udpPort);
  t.every(500,receiveTelem );
}

void loop() {
  t.update();
}
