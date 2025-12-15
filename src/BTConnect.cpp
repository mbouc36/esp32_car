#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>

BLECharacteristic *pCharacteristicTx;
bool deviceConnected = false;
uint8_t txValue = 0;
long lastMsg = 0;
String rxload="Test\n";

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define LED 2

void Parse_BLE_Tx(){
    if (deviceConnected&&rxload.length()>0) {
        Serial.println(rxload);;    
        if (rxload.equals("led_on")){
            Serial.println("LED on");
            digitalWrite(LED,HIGH);
        } else if (rxload.equals("led_off")){
            digitalWrite(LED,LOW);
        }
        rxload="";
    }
    
    if(Serial.available()>0){
        String str=Serial.readString();
        const char *newValue=str.c_str();
        pCharacteristicTx->setValue(newValue);
        pCharacteristicTx->notify();
    }
}

/* Callback class to manage connection to BLE */
class MyServerCallbacks: public BLEServerCallbacks { 
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) { 
    deviceConnected = false;
  } 
};

/* Callbacl class for when data is sent to ESP32 */
class MyCallbacks: public BLECharacteristicCallbacks { 
  void onWrite(BLECharacteristic *pCharacteristicRx) {
    std::string rxValue = pCharacteristicRx->getValue();
    if (rxValue.length() > 0) {
        rxload="";
        for (int i = 0; i < rxValue.length(); i++){
            rxload +=(char)rxValue[i];
      }
      Parse_BLE_Tx();
    } 
  }
};

void setupBLE(String BLEName){
  const char *ble_name=BLEName.c_str();
  BLEDevice::init(ble_name);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristicTx= pService->createCharacteristic(CHARACTERISTIC_UUID_TX,BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristicTx->addDescriptor(new BLE2902());
  BLECharacteristic *pCharacteristicTx = pService->createCharacteristic(CHARACTERISTIC_UUID_RX,BLECharacteristic::PROPERTY_WRITE);
  pCharacteristicTx->setCallbacks(new MyCallbacks()); 
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void BL_Rx_Setup() {
  Serial.begin(115200);
  setupBLE("ESP32_Bluetooth");
  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW);
}

