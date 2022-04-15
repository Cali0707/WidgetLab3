#include <ArduinoBLE.h>
#include <string.h>

typedef struct stringll {
    stringll* next;
    char* string;
} stringll;

typedef struct {
    stringll* data;
    int numLines;
    boolean isComplete;
} json;

stringll* init_stringll_node(int l) {
    stringll *node = (stringll*)malloc(sizeof(stringll));
    node->string = (char*)malloc(l * sizeof('a'));
    node->next = NULL;
    return node;
}

int i = 0;
char *message = (char*)malloc(512*sizeof('a'));
json* jsonData = (json*)malloc(sizeof(json));

stringll *node, *prev;
BLEDevice central;
BLECharacteristic stringCharacteristic;
BLECharacteristic numFieldsCharacteristic;


void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
//  while(!Serial) {
//    ;
//  }
  Serial1.begin(9600);
  jsonData->isComplete = false;
  jsonData->numLines = 0;
  if (!BLE.begin()) {
//    Serial.println("Unable to start ble");
    while(1);
  }
  BLE.setEventHandler(BLEDiscovered, bleCentralDiscoverHandler);

  BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
//  Serial.println("Scanning...");

}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial1.available()) {
    delay(2);
    char c = Serial1.read();
    if (c == '\0' || c == '{') {
      continue;
    } else if (c == '}') {
      node->string[i] = '\0';
//      jsonData->isComplete = true;
      jsonData->numLines--;
//      Serial.println("Processed event");
      receiveEvent();
//      Serial.println("Sent data over BLE!");
      jsonData->numLines = 0;
    } else if (c == '\n') {
      if (jsonData->numLines != 0) {
        prev = node;
        prev->string[i] = '\0';
        node = init_stringll_node(30);
        prev->next = node;
      } else {
        jsonData->data = init_stringll_node(30);
        jsonData->numLines = 0;
        node = jsonData->data;
      }
      i = 0;
      jsonData->numLines++;
      node->string[i] = c;
      i++;
    } else {
      node->string[i] = c;
      i++;
    }
  }
  BLE.poll();
}

void bleCentralDiscoverHandler(BLEDevice peripheral) {
//  Serial.println("Found peripheral!");
  BLE.stopScan();
  if (!peripheral.connect()) {
//    Serial.println("Failed to connect to peripheral");
    BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
    return;
  } else {
//    Serial.println("Connected to peripheral!");
  }
  // discover service
  if (peripheral.discoverService("19B10000-E8F2-537E-4F6C-D104768A1214")) {
//    Serial.println("Discovered service!");
  } else {
    peripheral.disconnect();
    BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
    return;
  }

  // find string characteristic
  stringCharacteristic = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");

  if (!stringCharacteristic) {
//    Serial.println("Could not find characteristic");

  } else {
//    Serial.println("Found characteristic!");
  }

  // find numFields characteristic
  numFieldsCharacteristic = peripheral.characteristic("19B10002-E8F2-537E-4F6C-D104768A1214");

  if (!numFieldsCharacteristic) {
//    Serial.println("Could not find numFields characteristic");
  } else {
//    Serial.println("Found characteristic");
  }
  return;

//  while(peripheral.connected()) {
//    while(Serial1.available()) {
//      delay(2);
//      char c = Serial1.read();
//      if (c == '\0' || c == '{') {
//        continue;
//      } else if (c == '}') {
//        node->string[i] = '\0';
//        jsonData->numLines--; // newlines will be overcounted by one otherwise because of newline before closing bracket
//        Serial.println("Processed event");
////        receiveEvent();
//        if (numFieldsCharacteristic.canWrite()) {
//          numFieldsCharacteristic.writeValue((byte)jsonData->numLines);
//          if (!numFieldsCharacteristic.subscribe()) {
//            numFieldsCharacteristic.writeValue((byte)0x00);
//          }
//        }
//        stringll* old;
//        stringCharacteristic.writeValue(jsonData->data->string, strlen(jsonData->data->string));
//        Serial.println("Wrote value");
//        jsonData->numLines--;
//        old = jsonData->data;
//        jsonData->data = jsonData->data->next;
//        free(old->string);
//        free(old);
//        while (jsonData->numLines > 0) {
//          if (numFieldsCharacteristic.valueUpdated()) {
//            boolean sentLine = false;
//            jsonData->numLines--;
//            while(!sentLine) {
//              if (stringCharacteristic.canWrite()) {
//                stringCharacteristic.writeValue(jsonData->data->string, strlen(jsonData->data->string));
//                Serial.println("Wrote value");
//                old = jsonData->data;
//                if (jsonData->data->next != NULL) {
//                  jsonData->data = jsonData->data->next;
//                }
//                free(old->string);
//                free(old);
//                sentLine = true;
//                Serial.println("Freed line");
//              }
//            }
//          }
//        }
//        Serial.println("Send data over BLE!");
//        jsonData->numLines = 0;
//      } else if (c == '\n') {
//        if (jsonData->numLines != 0) {
//          prev = node;
//          prev->string[i] = '\0';
//          node = init_stringll_node(30);
//          prev->next = node;
//        } else {
//          jsonData->data = init_stringll_node(30);
//          jsonData->numLines = 0;
//          node = jsonData->data;
//        }
//        i = 0;
//        jsonData->numLines++;
//        node->string[i] = c;
//        i++;
//      } else {
//        node->string[i] = c;
//        i++;
//      }
//    }
//  }
}

void receiveEvent() {
  if (numFieldsCharacteristic.canWrite()) {
//    Serial.println((byte)jsonData->numLines);
    numFieldsCharacteristic.writeValue((byte)jsonData->numLines);
//    Serial.println(numFieldsCharacteristic
    if (!numFieldsCharacteristic.subscribe()) {
      numFieldsCharacteristic.writeValue((byte)0x00);
    } else {
//      Serial.println("Subscribed to numFields!");
    }
  }
//      Serial.println("Unable to write numFields");
  stringll* old;
//  Serial.println(jsonData->numLines);
  stringCharacteristic.writeValue(jsonData->data->string, strlen(jsonData->data->string));
//  Serial.println("Wrote value");
  jsonData->numLines--;
  old = jsonData->data;
  jsonData->data = jsonData->data->next;
  free(old->string);
  free(old);
//  Serial.println("Freed first string");
  while (jsonData->numLines > 0) {
//    Serial.println((int)numFieldsCharacteristic.value());
    if (numFieldsCharacteristic.valueUpdated()) {
//      Serial.println("numFields updated");
      boolean sentLine = false;
      jsonData->numLines--;
      while(!sentLine) {
        if (stringCharacteristic.canWrite()) {
          stringCharacteristic.writeValue(jsonData->data->string, strlen(jsonData->data->string));
//          Serial.println("Wrote value");
          old = jsonData->data;
          if (jsonData->data->next != NULL) {
            jsonData->data = jsonData->data->next;
          }
          free(old->string);
          free(old);
          sentLine = true;
//          Serial.println("Freed line");
        }
      }

    }
  }
//      peripheral.disconnect();
//      Serial.println("Disconnected");
//  sentData = true;
  return;
//  BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
//  boolean sentData = false;
////  json* jsonData = initJson(message);
//  int numFields = jsonData->numLines;
//  Serial.print("numLines: ");
//  Serial.println(numFields);
////  Serial.println(numFields);
//  while (!sentData) {
//    BLEDevice peripheral = BLE.available();
////    Serial.println("Waiting for peripheral");
//    delay(10);
//    if (peripheral) {
//      Serial.println("Found peripheral");
//      // connect to peripheral
//      BLE.stopScan();
//      if (peripheral.connect()) {
//      Serial.println("Connected!");
//      } else {
//      Serial.println("Failed to connect");
//        return;
//      }
//      // discover service
//      if (peripheral.discoverService("19B10000-E8F2-537E-4F6C-D104768A1214")) {
//        Serial.println("Discovered service!");
//      } else {
//        peripheral.disconnect();
//        return;
//      }
//
//      // find string characteristic
//      BLECharacteristic stringCharacteristic = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");
//
//      if (!stringCharacteristic) {
//        Serial.println("Could not find characteristic");
//
//      } else {
//        Serial.println("Found characteristic!");
//      }
//
//      // find numFields characteristic
//      BLECharacteristic numFieldsCharacteristic = peripheral.characteristic("19B10002-E8F2-537E-4F6C-D104768A1214");
//
//      if (!numFieldsCharacteristic) {
//        Serial.println("Could not find numFields characteristic");
//      } else {
//        Serial.println("Found characteristic");
//      }
//
//      if (numFieldsCharacteristic.canWrite()) {
//        numFieldsCharacteristic.writeValue((byte)numFields);
//        if (!numFieldsCharacteristic.subscribe()) {
//          numFieldsCharacteristic.writeValue((byte)0x00);
//        }
//      }
////      Serial.println("Unable to write numFields");
//      stringll* old;
//      stringCharacteristic.writeValue(jsonData->data->string, strlen(jsonData->data->string));
//      Serial.println("Wrote value");
//      numFields--;
//      old = jsonData->data;
//      jsonData->data = jsonData->data->next;
//      free(old->string);
//      free(old);
//      while (numFields > 0) {
//        if (numFieldsCharacteristic.valueUpdated()) {
//          boolean sentLine = false;
//          numFields--;
//          while(!sentLine) {
//            if (stringCharacteristic.canWrite()) {
//              stringCharacteristic.writeValue(jsonData->data->string, strlen(jsonData->data->string));
//              Serial.println("Wrote value");
//              old = jsonData->data;
//              if (jsonData->data->next != NULL) {
//                jsonData->data = jsonData->data->next;
//              }
//              free(old->string);
//              free(old);
//              sentLine = true;
//              Serial.println("Freed line");
//            }
//          }
//
//        }
//      }
////      peripheral.disconnect();
////      Serial.println("Disconnected");
//      sentData = true;
//      return;
//    } else {
////      BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
//    }
//  }
}
