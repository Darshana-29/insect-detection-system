# Smart Grain Insect Detection System

An IoT-based grain monitoring system designed to detect conditions associated with insect infestation in stored grains using an ESP32 and multiple sensors.

## Overview

Stored grains can be affected by insect infestation, which may reduce their quality and quantity. This project provides continuous monitoring of storage conditions and activity-related parameters to identify abnormal conditions at an early stage.

The system uses an ESP32 as the main controller along with temperature and humidity, gas, and vibration sensors. The collected data is processed and monitored through the Blynk IoT platform.

## Components Used

- ESP32 DevKit V1
- DHT11 Temperature and Humidity Sensor
- MQ135 Gas Sensor
- SW-420 Vibration Sensor
- LED
- Buzzer
- Breadboard / PCB

## Working

1. The DHT11 sensor measures temperature and humidity.
2. The MQ135 sensor monitors gas levels.
3. The SW-420 sensor detects vibration associated with insect activity.
4. ESP32 processes the sensor readings.
5. The readings are compared with predefined threshold values.
6. When abnormal conditions are detected, the LED and buzzer provide an alert.
7. Sensor data is sent to the Blynk IoT platform for remote monitoring and notifications.

## Technologies Used

- ESP32
- Embedded C/C++
- Arduino IDE
- Sensor Interfacing
- Wi-Fi
- Blynk IoT
- Threshold-Based Detection

## Applications

- Grain storage facilities
- Agricultural warehouses
- Silos and godowns
- Seed storage
- Food processing and milling industries

## Advantages

- Continuous monitoring
- Early detection of abnormal conditions
- Multiple sensing parameters
- Remote monitoring through Blynk
- Reduced dependence on manual inspection
- Low-cost monitoring approach

## Future Scope

- Camera-based insect identification
- Machine-learning-based detection
- Cloud-based data logging
- Mobile application enhancements
- Automated temperature and humidity control

## Project Status

Completed

The prototype demonstrates sensor-based monitoring of temperature, humidity, gas level, and vibration, with local alerts and Blynk-based remote monitoring.
