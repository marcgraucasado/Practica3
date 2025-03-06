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
```

## 1. Informe del Funcionamiento, Salida por el Terminal y Visualización en Navegador de la Conexión a la Página Web
FUNCIONAMIENTO

El objetivo de este código es establecer un servidor web en un ESP32, en este caso, con mi móvil. Luego, este mostrará una página HTML cuando se acceda a través de un navegador web.

-Primeramente, el ESP32 se conecta a la red WiFi que le damos en el código:
```
const char* ssid = "Iphone de Marc"; // Enter your SSID here
const char* password = "12345678"; // Enter your Password here
```

-Creamos un objeto WebServer y se define una ruta. Esta se maneja con la función ```cpp handle_root(). ```

-La función handle_root() se llama cuando se accede al servidor web. Esta envía una respuesta, que en este caso será la página web.

SALIDA POR EL TERMINAL

Por el terminal podremos ver información sobre el WiFi y la dirección IP asignada al ESP32. Si se conecta correctamente a la red WiFi, mostrará un mensaje indicando la conexión exitosa y la dirección IP del ESP32.
```cpp
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
```


### Práctica B: Comunicación bluetooth con el móvil
## CÓDIGO:

```cpp
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup() {
 Serial.begin(115200);
 SerialBT.begin("ESP32 Marc"); 
 Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
 if (Serial.available()) {
   SerialBT.write(Serial.read());
 }
 if (SerialBT.available()) {
   Serial.write(SerialBT.read());
 }
 delay(20);
}
```


FUNCIONAMIENTO
En esta segunda parte de la práctica, vamos a utilizar la librería BluetoothSerial.h, que nos permitirá crear variables de tipo BluetoothSerial. Estas variables incluyen funciones que facilitan la conexión Bluetooth y permiten enviar y recibir mensajes entre el microcontrolador (MP) y un dispositivo conectado, creando un chat básico.

Primero, incluimos la librería y declaramos la variable SerialBT de tipo BluetoothSerial. Luego, en el void setup(), inicializamos el puerto serie. Utilizando la función .begin de la librería, nuestro MP creará una red Bluetooth que llamaremos "ESP32 Marc".

En el void loop, tenemos dos if que se ejecutan independientemente. Ambos cumplen la misma función, pero uno se activa si el puerto serie del MP está operativo, y el otro, si lo está el puerto serie del dispositivo conectado. Cuando estas condiciones se cumplen, el puerto serie del MP escribe lo que lee del puerto serie del dispositivo conectado y viceversa. De este modo, si envío un mensaje desde mi dispositivo, se mostrará en el puerto serie del MP, y si envío un mensaje desde el MP, se mostrará en el puerto serie del dispositivo, creando un chat rudimentario similar a una versión inicial de WhatsApp.

En la práctica, logramos establecer una conexión Bluetooth entre el MP y nuestros móviles. Usando la aplicación Serial Bluetooth Terminal, pudimos enviar mensajes tanto desde nuestros móviles al MP como del MP a nuestros móviles.
