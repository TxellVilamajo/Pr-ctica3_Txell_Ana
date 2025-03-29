#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// SSID & Password
const char* ssid = "FOCentelles_0631-ext";      // Introduïu el vostre SSID aquí
const char* password = "81551217";  // Introduïu la vostra contrasenya aquí

WebServer server(80);  // Objecte del servidor web al port 80

void handle_root() {
    File file = SPIFFS.open("/web_PD3.html", "r");
    if (!file) {
        server.send(500, "text/plain", "Error al carregar el fitxer HTML.");
        return;
    }

    String html = file.readString();
    server.send(200, "text/html", html);
    file.close();
}

void setup() {
    Serial.begin(115200);
   
    // Connexió WiFi
    Serial.println("Connectant a WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWiFi connectat!");
    Serial.print("IP assignada: ");
    Serial.println(WiFi.localIP());

    // Inicialització de SPIFFS per llegir arxius
    if (!SPIFFS.begin(true)) {
        Serial.println("Error muntant SPIFFS!");
        return;
    }

    // Definició de la ruta principal "/"
    server.on("/", handle_root);

    // Inici del servidor web
    server.begin();
    Serial.println("Servidor HTTP iniciat.");
}

void loop() {
    server.handleClient();
}