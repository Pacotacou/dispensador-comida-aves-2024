#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configura las credenciales de la red WiFi
const char* ssid = "COWIFI241590725/0";
const char* password = "WiFi-89589491";

// Configura la dirección del servidor MQTT
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

//Conectar al WiFi
void setup_wifi() {
  delay(10);
  // Conecta a la red WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}
// Conectar al servicdor MQTT
void reconnect() {
  // Ciclo hasta que se conecte
  while (!client.connected()) {
    Serial.print("Conectando al servidor MQTT...");
    // Intenta conectar
    if (client.connect("ESP8266Client")) {
      Serial.println("conectado");
    } else {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(" intenta de nuevo en 5 segundos");
      // Espera 5 segundos antes de reintentar
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Envia un mensaje cada 5 segundos
  long now = millis();
  static long lastMsg = 0;
  if (now - lastMsg > 5000) {
    lastMsg = now;
    // Crea un mensaje
    String msg = "Hola desde ESP8266 ";
    msg += String(now);
    // Publica el mensaje
    client.publish("nodemcu/test", (char*) msg.c_str());
    Serial.print("Mensaje enviado: ");
    Serial.println(msg);
  }
}
