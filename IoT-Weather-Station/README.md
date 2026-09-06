# IoT Weather Station

An IoT-based weather monitoring system using ESP32 and multiple sensors to monitor environmental conditions in real time.

## Features

- Temperature monitoring
- Humidity monitoring
- Atmospheric pressure monitoring
- Air quality monitoring
- Rain detection
- Wi-Fi connectivity
- ThingSpeak data monitoring

## Components Used

- ESP32
- DHT11
- BMP280
- MQ135
- Rain Sensor

## Software

- Arduino IDE
- Embedded C/C++
- ThingSpeak

## Working

The ESP32 collects data from the connected sensors and processes the readings. The measured environmental data is displayed through the Serial Monitor and transmitted to ThingSpeak using Wi-Fi.

## Sensor Data

| Sensor | Parameter |
|---|---|
| DHT11 | Temperature |
| DHT11 | Humidity |
| BMP280 | Atmospheric Pressure |
| MQ135 | Air Quality |
| Rain Sensor | Rain Detection |

## Project Status

Completed
