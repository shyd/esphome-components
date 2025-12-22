#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace water_level_sensor {

class WaterLevelSensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
public:
  WaterLevelSensor();
  void setup() override;
  void update() override;
  void dump_config() override;
};

} // namespace water_level_sensor
} // namespace esphome
