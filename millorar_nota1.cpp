#include <WiFi.h>
#include <WebServer.h>

// Nom de la xarxa (SSID) i contrasenya per al punt d'accés
const char* ssid = "ESP32-AP"; // El nom de la xarxa Wi-Fi del teu ESP32
const char* password = "123456789"; // Contrasenya per connectar-se a l'AP

WebServer server(80); // Objecte WebServer (port HTTP, el port per defecte és 80)

// Declaració avançada de la funció handle_root
void handle_root();

void setup() {
  // Inicialitzem el port sèrie
  Serial.begin(115200);
  Serial.println("Creant punt d'accés...");
  
  // Configurar el ESP32 com a punt d'accés (Access Point)
  WiFi.softAP(ssid, password);  // Crear el punt d'accés amb el SSID i la contrasenya
  Serial.println("Punt d'accés creat.");

  // Mostrar la IP del punt d'accés
  Serial.print("Adreça IP del AP: ");
  Serial.println(WiFi.softAPIP()); // Mostra l'IP del punt d'accés

  // Definir la ruta principal ("/") i la funció que l'hi gestionarà
  server.on("/", handle_root);

  // Iniciar el servidor HTTP
  server.begin();
  Serial.println("Servidor HTTP iniciat.");
}

void loop() {
  // Gestionar les peticions HTTP entrants
  server.handleClient();
}

// Contingut HTML per mostrar a la web del servidor
String HTML = "<!DOCTYPE html>\
               <html>\
               <body>\
               <h1>My Primera Pagina con ESP32 - Access Point Mode &#128522;</h1>\
               </body>\
               </html>";

// Gestionar la URL de la pàgina principal (/)
void handle_root() {
  server.send(200, "text/html", HTML); // Enviar el contingut HTML al navegador
}