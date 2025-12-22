#include "water_level_sensor.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace water_level_sensor {

static const char *TAG = "water_level_sensor";

#define ATTINY1_HIGH_ADDR 0x78
#define ATTINY2_LOW_ADDR 0x77
#define THRESHOLD 100

WaterLevelSensor::WaterLevelSensor() : PollingComponent() {}

void WaterLevelSensor::setup() {

}

void WaterLevelSensor::dump_config() {
  LOG_SENSOR("", "Water Level Sensor", this);
  LOG_I2C_DEVICE(this);
}

void WaterLevelSensor::update() {
  uint8_t low_data[8] = {0};
  uint8_t high_data[12] = {0};

  // --- Read Low 8 Section ---
  // Corresponds to getLow8SectionValue() in .ino
  if (this->bus_->read(ATTINY2_LOW_ADDR, low_data, 8) != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to read from low address 0x%02X", ATTINY2_LOW_ADDR);
    this->status_set_warning();
    return;
  }

  // Small delay between reads as in the Seeed example code
  delay(10);

  // --- Read High 12 Section ---
  // Corresponds to getHigh12SectionValue() in .ino
  if (this->bus_->read(ATTINY1_HIGH_ADDR, high_data, 12) != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to read from high address 0x%02X", ATTINY1_HIGH_ADDR);
    this->status_set_warning();
    return;
  }

  this->status_clear_warning();

  // --- Process Data ---
  uint32_t touch_val = 0;
  uint8_t trig_section = 0;

  // Check low section thresholds
  for (int i = 0; i < 8; i++) {
    if (low_data[i] > THRESHOLD) {
      touch_val |= 1 << i;
    }
  }
  // Check high section thresholds
  for (int i = 0; i < 12; i++) {
    if (high_data[i] > THRESHOLD) {
      touch_val |= (uint32_t)1 << (8 + i);
    }
  }

  // Count consecutive sections from the bottom
  while (touch_val & 0x01) {
    trig_section++;
    touch_val >>= 1;
  }

  float water_level = trig_section * 5.0;

  ESP_LOGD(TAG, "Water Level: %.1f%% (Sections: %d)", water_level,
           trig_section);
  this->publish_state(water_level);
}

} // namespace water_level_sensor
} // namespace esphome
