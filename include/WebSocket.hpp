#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <AsyncTCP.h>

class WebSocketServer
{
public:
    WebSocketServer();
    void begin(AsyncWebServer *server);
    void loop();

private:
    AsyncWebSocket ws;
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                 AwsEventType type, void *arg, uint8_t *payload, size_t len);
};