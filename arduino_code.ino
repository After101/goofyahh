
#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncWebSocket.h>

const char *ssid = "Verma_act_5G_EXT";
const char *password = "Verma2024";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->opcode == WS_TEXT) {
    String message = "";
    for (size_t i = 0; i < len; i++) {
      message += (char)data[i];
    }
    
    if (message == "LED_ON") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Button clicked: Turn LED On");
    } else if (message == "LED_OFF") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Button clicked: Turn LED Off");
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ws.onEvent(handleWebSocketMessage);
  server.addHandler(&ws);

  // Enable CORS (Cross-Origin Resource Sharing)
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");

  server.begin();
}

void loop() {
}
