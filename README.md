# PR3-Marc  

## PRÁCTICA 3: WIFI y BLUETOOTH  

### Práctica A: Generación de una Página Web  

#### CÓDIGO:  

```cpp
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
```

## 1. Informe del Funcionamiento, Salida por el Terminal y Visualización en Navegador de la Conexión a la Página Web
FUNCIONAMIENTO

El objetivo de este código es establecer un servidor web en un ESP32, en este caso, con mi móvil. Luego, este mostrará una página HTML cuando se acceda a través de un navegador web.

-Para empezar, el ESP32 se conecta a la red WiFi que le damos en el código:
```
const char* ssid = "Iphone de Marc"; // Enter your SSID here
const char* password = "12345678"; // Enter your Password here
```

-Creamos un objeto WebServer y se define una ruta. Esta se maneja con la función ```handle_root(). ```

-La función ```handle_root()``` se llama cuando se accede al servidor web. Esta envía una respuesta, que en este caso será la página web.

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
#### CÓDIGO:

```cpp
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer;
BLECharacteristic* pCharacteristic;
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(9600);

  BLEDevice::init("ESP32S3");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService* pService = pServer->createService(BLEUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b"));
  pCharacteristic = pService->createCharacteristic(
                      BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"),
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  // Set security to none
  // pCharacteristic->setSecurity(BLE_SECURITY_NO_ACCESS);

  pService->start();
  BLEAdvertising* pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  if (deviceConnected) {
    if (Serial.available()) {
      pCharacteristic->setValue((uint8_t*)Serial.read(), 1);
      pCharacteristic->notify();
    }
  }
}
```

FUNCIONAMIENTO

En esta segunda parte de la práctica, vamos a utilizar la librería BluetoothSerial.h, que nos permitirá crear variables de tipo BluetoothSerial. Estas variables incluyen funciones que facilitan la conexión Bluetooth y permiten enviar y recibir mensajes entre el microcontrolador (MP) y un dispositivo conectado, creando un chat básico.

Primero, incluimos la librería y declaramos la variable SerialBT de tipo BluetoothSerial. Luego, en el void setup(), inicializamos el puerto serie. Utilizando la función .begin de la librería, nuestro MP creará una red Bluetooth que llamaremos "ESP32 Marc".

En el void loop, tenemos dos if que se ejecutan independientemente. Ambos cumplen la misma función, pero uno se activa si el puerto serie del MP está operativo, y el otro, si lo está el puerto serie del dispositivo conectado. Cuando estas condiciones se cumplen, el puerto serie del MP escribe lo que lee del puerto serie del dispositivo conectado y viceversa. De este modo, si envío un mensaje desde mi dispositivo, se mostrará en el puerto serie del MP, y si envío un mensaje desde el MP, se mostrará en el puerto serie del dispositivo, creando un chat rudimentario similar a una versión inicial de WhatsApp.

En la práctica, logramos establecer una conexión Bluetooth entre el MP y nuestros móviles. Usando la aplicación Serial Bluetooth Terminal, pudimos enviar mensajes tanto desde nuestros móviles al MP como del MP a nuestros móviles.
