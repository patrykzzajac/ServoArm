#include "WebServer.hpp"
#include "config.h"
#include <SPIFFS.h>

WebServer::WebServer() : server(80) {}

void WebServer::begin()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    setupSPIFFS();
    handleRoutes(server);
    server.begin();
    Serial.println("Web server started");
}

AsyncWebServer *WebServer::getServer()
{
    return &server;
}

void WebServer::setupSPIFFS()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully");
}

File WebServer::loadFromSPIFFS(String path, String contentType)
{
    File file = SPIFFS.open(path, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return file;
    }
    return file;
}

// Routes

void WebServer::handleRoutes(AsyncWebServer &server)
{
    server.on("/", HTTP_GET, std::bind(&WebServer::handleRoot, this, std::placeholders::_1));
    server.onNotFound(std::bind(&WebServer::handleNotFound, this, std::placeholders::_1));
}

void WebServer::handleRoot(AsyncWebServerRequest *request)
{
    File file = loadFromSPIFFS("/index.html", "text/html");
    if (!file)
    {
        request->send(500, "text/plain", "Failed to open file");
        return;
    }
    String content = "";
    while (file.available())
    {
        content += String((char)file.read());
    }
    file.close();
    request->send(200, "text/html", content);
}

void WebServer::handleNotFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not Found");
}