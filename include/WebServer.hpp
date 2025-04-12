#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

static AsyncWebSocket ws("/ws");

class WebServer
{
public:
    WebServer();
    void begin();
    AsyncWebServer *getServer(); // Method to get the server instance
private:
    AsyncWebServer server;
    void setupSPIFFS();
    File loadFromSPIFFS(String path, String contentType);
    void handleRoutes(AsyncWebServer &server);

    // routes
    void handleRoot(AsyncWebServerRequest *request);
    void handleNotFound(AsyncWebServerRequest *request);
};