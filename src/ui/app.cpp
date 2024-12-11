#include "app.h"
#include "EEPROM.h"
#include <Wire.h>
#include "../../lib/YOBA/src/number.h"

App& App::getInstance() {
	static App instance;

	return instance;
}

void App::setup() {
	// Config
	config.read();

	// Fan & atomizer
	pinMode(constants::pinout::fan, OUTPUT);
	pinMode(constants::pinout::atomizer, OUTPUT);

	// Encoder
	encoder.setup();

	// Configuring deep sleep interrupt wakeup source
	// It will check for human-to-encoder interactions in this case
	esp_sleep_enable_ext1_wakeup(
		1 << constants::pinout::encoder::sw
//		| 1 << constants::pinout::encoder::dt
//		| 1 << constants::pinout::encoder::clk
		,
		ESP_EXT1_WAKEUP_ALL_LOW
	);

	// Screen
	screenBuffer.setup();

	// UI
	menu.setup();

	// Temperature & humidity sensor
	_dht.setup(constants::pinout::temperatureAndHumiditySensor, DHTesp::DHT22);

	updateShutdownTimeConditional();
	updateFanAndAtomizerPower();
}

void App::tick() {
	readSensors();

	screenBuffer.clear(&Theme::black);

	menu.render();

	// Shutdown timer
	if (config.shutdownDelay > 0) {
		if (encoder.wasInterrupted()) {
			encoder.acknowledgeInterrupt();

			updateShutdownTime();
		}
		else {
			if (millis() >= _shutdownTime) {
				esp_deep_sleep_start();
			}
		}
	}

	screenBuffer.flush();

	config.tick();
}

void App::updateShutdownTime() {
	_shutdownTime = millis() + config.shutdownDelay * 60000;
//_shutdownTime = millis() + 5000;
}

void App::updateShutdownTimeConditional() {
	if (config.shutdownDelay > 0) {
		updateShutdownTime();
	}
	else {
		_shutdownTime = 0;
	}
}

void App::analogWriteToDevice(uint8_t pin, uint8_t value) {
	analogWriteFrequency(16000);
	analogWriteResolution(8);
	analogWrite(pin, 0xFF - value);
}

void App::updateFanPower() const {
	analogWriteToDevice(constants::pinout::fan, config.fanPower);
}

void App::updateAtomizerPower() const {
	analogWriteToDevice(constants::pinout::atomizer, config.atomizerPower);
}

void App::updateFanAndAtomizerPower() const {
	updateFanPower();
	updateAtomizerPower();
}

void App::readSensors() {
	if (millis() < _sensorsTickTime)
		return;

	_humidity = _dht.getHumidity();
	_temperature = _dht.getTemperature();

	_sensorsTickTime = millis() + _dht.getMinimumSamplingPeriod();
}

float App::getTemperature() const {
	return _temperature;
}

float App::getHumidity() const {
	return _humidity;
}

uint32_t App::getShutdownTime() const {
	return _shutdownTime;
}
