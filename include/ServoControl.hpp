#pragma once
#include <ESP32Servo.h>

extern class ServoControl servoControl;

class ServoControl
{
public:
    Servo servoArm1;
    Servo servoArm2;
    Servo servoGrip;
    Servo servoBase;
    ServoControl();
    void begin();
    void setAngle(Servo *servo, int angle);
};