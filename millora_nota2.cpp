#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Definir el nombre del dispositivo y las características
#define SERVICE_UUID           "0000181C-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID    "00002A74-0000-1000-8000-00805F9B34FB"

// Crear un servidor BLE
BLECharacteristic *pCharacteristic;

// Crear el servidor BLE
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("Cliente conectado");
    };

    void onDisconnect(BLEServer* pServer) {
        Serial.println("Cliente desconectado");
    }
};

void setup() {
    // Inicializar la comunicación serial
    Serial.begin(115200);
    Serial.println("Iniciando BLE...");

    // Inicializar BLE
    BLEDevice::init("ESP32 BLE Server");

    // Crear el servidor BLE
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Crear un servicio BLE
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Crear una característica BLE
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ |
                        BLECharacteristic::PROPERTY_WRITE
                      );

    // Configurar el valor inicial de la característica
    pCharacteristic->setValue("Hola desde ESP32!");

    // Iniciar el servicio
    pService->start();

    // Empezar a publicitar el dispositivo BLE
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
    Serial.println("Esperando cliente...");
}

void loop() {
    // En el loop no es necesario hacer nada si solo estamos esperando conexiones
    delay(2000);
}
