#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// wifi
const char *ssid = "nomeDaRedeSSID";                 // nome da sua rede wifi
const char password = "senhaDaRede";                 // senha da sua rede wifi
const char mqtt_server = "mqtt.eclipseprojects.io";  // servidor mqtt

int PulseSensorPin = A0;  // sensor de pulso conectado ao pino analógico A0 do nodemcu
int buzzerPin = 14;       // buzzer conectado ao pino digital D5 do nodemcu (GPIO14)

int Signal;           // armazena o valor bruto do sinal do sensor
int Threshold = 572;  // determina o limite para detectar um batimento cardíaco

unsigned long lastBeatTime = 0;  // momento da última detecção de batimento
unsigned int bpm = 0;            // armazena o batimento cardíaco por minuto

WiFiClient espClient;            // cria um objeto WiFiClient para gerenciar a conexão WiFi
PubSubClient client(espClient);  // cria um objeto PubSubClient e passa o WiFiClient como parâmetro para gerenciar a comunicação MQTT

void setup() {
  pinMode(buzzerPin, OUTPUT);  // define o pino do buzzer como saída
  Serial.begin(115200);        // inicia a comunicação serial
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");  // tenta conectar ao wifi
  }
  Serial.println("Connected to the WiFi network");  // conexão wifi estabelecida
  client.setServer(mqtt_server, 1883);              // configura o servidor mqtt
}

void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // cria um id de cliente aleatório
    String clientId = "IoT_Sens0r_Cardiac0_Mackenzie";
    clientId += String(random(0xffff), HEX);
    // tenta conectar
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");  // conexão mqtt estabelecida
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // espera 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}

void publish_mqtt() {
  client.publish("esp.mackenzie/sensorcardiaco", String(bpm).c_str(), true);  // publica os dados do bpm no tópico mqtt
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();  // reconecta ao mqtt se desconectado
  }

  publish_mqtt();  // publica os dados do bpm

  Signal = analogRead(PulseSensorPin);  // lê o valor do sensor de pulso

  if (Signal > Threshold) {
    if ((millis() - lastBeatTime) > 200) {      // verifica se passou tempo suficiente desde o último batimento
      bpm = 60000 / (millis() - lastBeatTime);  // calcula o bpm
      lastBeatTime = millis();                  // atualiza o momento da última detecção de batimento
    }
  }

  if (bpm > 150) {
    digitalWrite(buzzerPin, HIGH);  // liga o buzzer quando o bpm é maior que 150
  } else {
    digitalWrite(buzzerPin, LOW);  // desliga o buzzer caso contrário
  }

  // imprime o bpm a cada segundo
  static unsigned long lastPrintTime = 0;
  if (millis() - lastPrintTime >= 1000) {
    Serial.print("BPM: ");
    Serial.println(bpm);
    lastPrintTime = millis();
  }
  delay(20);  // pequena pausa antes da próxima leitura do sensor
}