#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Configurar el ESP32 como Access Point
const char* ssid = "Renatooo";  // Nombre de la red WiFi
const char* password = "1234567AB";  // Contraseña de la red

WebServer server(80);  // Servidor web en el puerto 80

// Declaración de función
void handle_root();

void setup() {
    Serial.begin(9600);

    // Configurar ESP32 como Access Point
    Serial.println("Configurando Access Point...");
    WiFi.softAP(ssid, password); 

    IPAddress IP = WiFi.softAPIP();  // Obtener la IP del ESP32
    Serial.print("Access Point iniciado con IP: ");
    Serial.println(IP);

    server.on("/", handle_root);  // Manejar la página principal
    server.begin();  // Iniciar servidor web
    Serial.println("Servidor HTTP iniciado");
}

void loop() {
    server.handleClient();  // Manejar las peticiones web
}

// Página HTML que se mostrará en el navegador
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>ESP32 en Modo Access Point &#128522;</h1>\
<p>¡Conéctate a este punto de acceso!</p>\
</body>\
</html>";

// Manejar la petición en "/"
void handle_root() {
    server.send(200, "text/html", HTML);
}