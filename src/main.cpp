#include <Arduino.h>
#include "ServoControl.hpp"
#include "WebServer.hpp"
#include "WebSocket.hpp"

ServoControl servoControl;
WebServer webServer;
WebSocketServer webSocketServer;

void setup()
{
    Serial.begin(115200);
    servoControl.begin();
    servoControl.setAngle(&servoControl.servoArm1, 90);
    servoControl.setAngle(&servoControl.servoArm2, 90);
    servoControl.setAngle(&servoControl.servoGrip, 90);
    servoControl.setAngle(&servoControl.servoBase, 90);

    webServer.begin();
    webSocketServer.begin(webServer.getServer());
}

void loop()
{
    webSocketServer.loop();
}
