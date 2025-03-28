#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Definir el nom del dispositiu i les característiques
#define SERVICE_UUID           "0000181C-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID    "00002A74-0000-1000-8000-00805F9B34FB"

// Crear un servidor BLE
BLECharacteristic *pCharacteristic;

// Crear el servidor BLE
class MyServerCallbacks: public BLEServerCallbacks {
    // Quan un client es connecta
    void onConnect(BLEServer* pServer) {
        Serial.println("Client connectat");
    };

    // Quan un client es desconnecta
    void onDisconnect(BLEServer* pServer) {
        Serial.println("Client desconnectat");
    }
};

void setup() {
    // Inicialitzar la comunicació per port sèrie
    Serial.begin(115200);
    Serial.println("Iniciant BLE...");

    // Inicialitzar BLE amb el nom "ESP32 BLE Server"
    BLEDevice::init("ESP32 BLE Server");

    // Crear el servidor BLE
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());  // Assignem els callbacks per les connexions

    // Crear un servei BLE amb el UUID especificat
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Crear una característica BLE (llegir i escriure)
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ |  // Permet llegir el valor de la característica
                        BLECharacteristic::PROPERTY_WRITE  // Permet escriure a la característica
                      );

    // Configurar el valor inicial de la característica
    pCharacteristic->setValue("Hola des de ESP32!");

    // Iniciar el servei BLE
    pService->start();

    // Començar a publicitar el dispositiu BLE (perquè altres dispositius el puguin detectar)
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
    
    // Mostrar missatge a la consola sèrie
    Serial.println("Esperant client...");
}

void loop() {
    // En aquest cas no cal fer res al loop, només s'espera la connexió
    delay(2000); // Espera de 2 segons abans de repetir el bucle
}
