
#include "WebSocket.hpp"
#include <ArduinoJson.h>
#include "ServoControl.hpp"

WebSocketServer::WebSocketServer() : ws("/ws") {}

void WebSocketServer::begin(AsyncWebServer *server)
{
    ws.onEvent(std::bind(&WebSocketServer::onEvent, this, std::placeholders::_1,
                         std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
                         std::placeholders::_5, std::placeholders::_6));
    server->addHandler(&ws);
    Serial.println("WebSocket server started");
}

void WebSocketServer::loop()
{
    ws.cleanupClients();
}

void WebSocketServer::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                              AwsEventType type, void *arg, uint8_t *payload, size_t len)
{
    switch (type)
    {
    case AwsEventType::WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case AwsEventType::WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(),
                      client->remoteIP().toString().c_str());
        break;
    case AwsEventType::WS_EVT_DATA:
    {
        // Parse JSON payload
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload, len);
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
        }

        const char *command = doc["command"];

        if (strcmp(command, "grip") == 0)
        {
            int angle = doc["angle"];
            servoControl.setAngle(&servoControl.servoGrip, angle);
        }
        else if (strcmp(command, "base") == 0)
        {
            int angle = doc["angle"];
            servoControl.setAngle(&servoControl.servoBase, angle);
        }
        else if (strcmp(command, "servo1") == 0)
        {
            int angle = doc["angle"];
            servoControl.setAngle(&servoControl.servoArm1, angle);
        }
        else if (strcmp(command, "servo2") == 0)
        {
            int angle = doc["angle"];
            servoControl.setAngle(&servoControl.servoArm2, angle);
        }
        else
        {
            Serial.print("Unknown command: ");
            Serial.println(command);
        }

        break;
    }
    case AwsEventType::WS_EVT_ERROR:
        Serial.printf("WebSocket client #%u error: %u\n", client->id(), *(uint16_t *)arg);
        break;
    }
}