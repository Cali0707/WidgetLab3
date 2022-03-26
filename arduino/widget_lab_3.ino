#include <SPI.h>
#include <WiFiNINA.h>
#include "secrets.h"

char ssid[] = NETWORK_SSID;        // your network SSID (name)
char pass[] = NETWORK_PASSWORD;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                  // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = SERVER;    // name address for server e.g. www.google.com

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP, 443 for HTTPS):

WiFiSSLClient client;

void setup() {

  //Initialize serial and wait for port to open:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  // check for the WiFi module:

  if (WiFi.status() == WL_NO_MODULE) {

    Serial.println("Communication with WiFi module failed!");

    // don't continue

    while (true);

  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {

    Serial.println("Please upgrade the firmware");
    // If you get this message, please go to https://docs.arduino.cc/tutorials/nano-rp2040-connect/rp2040-upgrading-nina-firmware
  }

  // attempt to connect to WiFi network:

  while (status != WL_CONNECTED) {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:

    delay(10000);

  }

  Serial.println("Connected to wifi");

  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // TODO: implement function to generate the request body
  String requestBody = "{\n    \"deviceId\": 1234,\n    \"thermistorValue\": 500,\n    \"photoResistorValue\": 20\n}";
  Serial.println(requestBody);
  postData(requestBody);

}

void loop() {

  // if there are incoming bytes available

  // from the server, read them and print them:

  while (client.available()) {

    char c = client.read();

    Serial.write(c);

  }

  // if the server's disconnected, stop the client:

  if (!client.connected()) {

    Serial.println();

    Serial.println("disconnecting from server.");

    client.stop();

    // do nothing forevermore:

    while (true);

  }
}

void printWiFiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your board's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
}

void postData(String body) {
  // Check if WiFi is connected
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected to the server...");
    // Connect to the server on https port
    if (client.connect(server, 443)){
      // make post request & send headers
      client.println("POST /sensors/add-data HTTP/1.1");
      client.println("Host: " + String(server));
      client.println("Content-Type: application/json");
      client.println("Accept: */*");
      client.println("Cache-Control: no-cache");
      client.println("Accept-Encoding: gzip, deflate");
      client.println("Accept-Language: en-us");
      client.println("Content-Length: " + String(body.length())); //ANSWER: body.length() needs to be wrapped as a string, see above
      client.println("Connection: close");
      client.println(); // end HTTP request header
      client.println(body);
    }
  }
}

