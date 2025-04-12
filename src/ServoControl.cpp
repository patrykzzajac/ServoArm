#include "ServoControl.hpp"
#include "config.h"

ServoControl::ServoControl()
{
}

void ServoControl::begin()
{
    servoArm1.attach(SERVO_ARM1_PIN);
    servoArm2.attach(SERVO_ARM2_PIN);
    servoGrip.attach(SERVO_GRIP_PIN);
    servoBase.attach(SERVO_BASE_PIN);
}
void ServoControl::setAngle(Servo *servo, int angle)
{
    if (angle < 0)
    {
        angle = 0;
    }
    else if (angle > 180)
    {
        angle = 180;
    }
    servo->write(angle);
}