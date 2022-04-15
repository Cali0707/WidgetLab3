#include <ArduinoBLE.h>
#include <Wire.h>
#include <string.h>

BLEService jsonService("19B10000-E8F2-537E-4F6C-D104768A1214"); // create service

// create switch characteristic and allow remote device to read and write
int valueSize = sizeof("") * 512;
BLECharacteristic stringCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, valueSize, false);
BLEUnsignedIntCharacteristic numFieldsCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify);
//BLEBooleanCharacteristic canWriteCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead);

char jsonData[512] = "";

void setup() {
//
//  Serial.begin(9600);
//  while(!Serial) {
//    ;
//  }
  Serial1.begin(9600);
  // begin initialization
//  Wire.begin();
  if (!BLE.begin()) {
//    //Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set the local name peripheral advertises
//  BLE.setLocalName("LEDCallback");
  // set the UUID for the service this peripheral advertises
  BLE.setAdvertisedService(jsonService);

//  canWriteCharacteristic.writeValue(true);

  // add the characteristic to the service
  jsonService.addCharacteristic(stringCharacteristic);
  jsonService.addCharacteristic(numFieldsCharacteristic);
//  jsonService.addCharacteristic(canWriteCharacteristic);

  // add service
  BLE.addService(jsonService);

  // assign event handlers for connected, disconnected to peripheral
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  stringCharacteristic.setEventHandler(BLEWritten, stringCharacteristicWritten);
  numFieldsCharacteristic.setEventHandler(BLEWritten, numFieldsCharacteristicWritten);
  // set an initial value for the characteristic
//  stringCharacteristic.setValue("Test", sizeof("Test"));

  // start advertising
  BLE.advertise();
//  Serial.println("Advertising");

//  Serial.println(("Bluetooth® device active, waiting for connections..."));
}

void loop() {
  // poll for Bluetooth® Low Energy events
  BLE.poll();
}

void blePeripheralConnectHandler(BLEDevice central) {
//  central connected event handler
//  Serial.print("Connected event, central: ");
//  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
//  central disconnected event handler
//  Serial.print("Disconnected event, central: ");
//  Serial.println(central.address());
}

void stringCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  // central wrote new value to characteristic, update LED
  ////Serial.print("Characteristic event, written: ");
  int numFields = numFieldsCharacteristic.value();
  if (numFields >= 1) {
    int charSize = stringCharacteristic.valueLength();
    char value[charSize];
    stringCharacteristic.readValue(value, charSize);
    value[charSize] = 0;
//    strcat(jsonData, "\n\t");
    strcat(jsonData, value);
    //Serial.println(jsonData);

//    //Serial.println(jsonData);
    numFieldsCharacteristic.writeValue(numFields - 1);
    if (numFields == 1) {
      strcat(jsonData, "\n}");
      int stringLength = strlen(jsonData);
      Serial1.write(jsonData, stringLength);
//      strcpy(jsonData, "");
//      Serial.print("Data: ");
//      Serial.println(jsonData);

      for (int i = 0; i < stringLength; i++) {
        jsonData[i] = '\0';
      }
//      Serial.println(jsonData);
  //    sendMessage(value, 2);
    }
  }
}

void numFieldsCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  //Serial.print("Num fields: ");
  if (numFieldsCharacteristic.value() > 0) {
    jsonData[0] = '{';
  }
  //Serial.println(numFieldsCharacteristic.value());
//  canWriteCharacteristic.writeValue(false);
}

void sendMessage(const char* message, int address) {
  //Serial.println(message);
  Wire.beginTransmission(address);
  Wire.write(message);
  Wire.endTransmission();
}
