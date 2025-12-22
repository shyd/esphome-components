# ESPHome Water Level Sensor Component

This project provides a custom ESPHome component for a specific I2C Water Level Sensor (often associated with Seeed Studio or similar hardware using ATTiny chips).

## Project Structure

```text
.
├── components/
│   └── water_level_sensor/  # Custom Component Source Code
│       ├── README.md        # Component documentation
│       ├── __init__.py
│       ├── sensor.py
│       ├── water_level_sensor.cpp
│       └── water_level_sensor.h
├── waterlevel_example.yaml  # Example ESPHome configuration
└── secrets.yaml             # Secrets file (wifi credentials, etc.)
```

## Getting Started

### Prerequisites

- [ESPHome](https://esphome.io/) installed.
- An ESP32 or ESP8266 board.
- The Water Level Sensor hardware connected via I2C.

### Installation

1. Clone or download this repository.
2. Create a `secrets.yaml` file with your WiFi credentials:

    ```yaml
    wifi_ssid: "YOUR_SSID"
    wifi_password: "YOUR_PASSWORD"
    ```

3. Edit `waterlevel_example.yaml` to match your board type and pin configuration if necessary.

### Usage

To build and upload the firmware to your device:

```bash
esphome run waterlevel_example.yaml
```

## Component Details

The custom component is located in `components/water_level_sensor`. It handles the low-level I2C communication with the sensor's two addresses (`0x77` and `0x78`) to calculate the water level percentage.

For more details on the component configuration and hardware requirements, please refer to the [Component README](components/water_level_sensor/README.md).
