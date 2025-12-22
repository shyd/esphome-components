import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_PERCENT, ICON_WATER
from esphome.components import i2c

DEPENDENCIES = ['i2c']

water_level_sensor_ns = cg.esphome_ns.namespace('water_level_sensor')
WaterLevelSensor = water_level_sensor_ns.class_('WaterLevelSensor', cg.PollingComponent, i2c.I2CDevice)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        WaterLevelSensor,
        unit_of_measurement=UNIT_PERCENT,
        accuracy_decimals=1,
        icon=ICON_WATER
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x01))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    await sensor.register_sensor(var, config)
