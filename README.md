# PR3-Marc  

## PRÁCTICA 3: WIFI y BLUETOOTH  

### Práctica A: Generación de una Página Web  

### CÓDIGO:  

```cpp
#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "Iphone de Marc"; // Enter your SSID here
const char* password = "12345678"; // Enter your Password here

WebServer server(80); // Object of WebServer(HTTP port, 80 is default)

void setup() {
    Serial.begin(115200);
    Serial.println("Try Connecting to ");
    Serial.println(ssid);

    // Connect to your wi-fi modem
    WiFi.begin(ssid, password);

    // Check wi-fi is connected to network
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP()); // Show ESP32 IP on serial

    server.on("/", handle_root);
    server.begin();
    Serial.println("HTTP server started");
    delay(100);
}

void loop() {
    server.handleClient();
}

// HTML & CSS contents displayed on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
    server.send(200, "text/html", HTML);
}

1. Informe del Funcionamiento, Salida por el Terminal y Visualización en Navegador de la Conexión a la Página Web
 FUNCIONAMIENTO

El objetivo de este código es establecer un servidor web en un ESP32, en este caso, con mi móvil. Luego, este mostrará una página HTML cuando se acceda a través de un navegador web.

Primeramente, el ESP32 se conecta a la red WiFi que le damos en el código:
```cpp
const char* ssid = "Iphone de Marc"; // Enter your SSID here
const char* password = "12345678"; // Enter your Password here

Creamos un objeto WebServer y se define una ruta. Esta se maneja con la función handle_root().

La función handle_root() se llama cuando se accede al servidor web. Esta envía una respuesta, que en este caso será la página web.

SALIDA POR EL TERMINAL

Por el terminal podremos ver información sobre el WiFi y la dirección IP asignada al ESP32. Si se conecta correctamente a la red WiFi, mostrará un mensaje indicando la conexión exitosa y la dirección IP del ESP32.
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
 }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
  server.on("/", handle_root);
    server.begin();
  Serial.println("HTTP server started");
  delay(100);

### Práctica B: comunicación bluetooth con el movil
