#include <ArduinoBLE.h>


BLEService StringService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
//char initialValue[] = "test";
int valueSize = sizeof("") * 255;
BLECharacteristic StringCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify | BLEWrite, valueSize, false);
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Hello!");
//  pinMode(buttonPin, INPUT_PULLUP);
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");
  }
  // set advertised local name and service UUID:
  BLE.setDeviceName("Arduino");
  BLE.setAdvertisedService(StringService);
  // add the characteristic to the service
  StringService.addCharacteristic(StringCharacteristic);
  // add service
  BLE.addService(StringService);
  // start advertising
  BLE.advertise();
  Serial.println("BLE LED Peripheral, waiting for connections....");
}
void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    // while the central is still connected to peripheral:
    while (central.connected()) {
      if (StringCharacteristic.written()) {
        int charSize = StringCharacteristic.valueLength();
        Serial.println(charSize);
        char value[charSize];
//        Serial.println((char)StringCharacteristic.read());
        StringCharacteristic.readValue(value, charSize);
        value[charSize] = 0;
        Serial.println(value);
      }
    }
    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
