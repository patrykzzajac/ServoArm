# ESP32 Robotic Arm

This is custom control code for this project:
https://makerworld.com/en/models/1290483-servo-mini-arm#profileId-1320674

## Prerequisites

1. PlatformIO

## How to use it

1. Configure wifi and servo pins in `include/config.h`
2. Flash the program to the esp32 (don't forget to upload Filesystem Image)
3. When the esp32 connects to WiFi, it will print it's IP address in serial monitor
4. Go to the IP address with a web browser
