#include "app.h"
#include "EEPROM.h"
#include <Wire.h>
#include "../../lib/YOBA/src/number.h"

App& App::getInstance() {
	static App instance;

	return instance;
}

void App::setup() {
	Serial.begin(115200);

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
	atmosphericSensor.setup(constants::pinout::atmosphericSensor, DHTesp::DHT22);

	updateFanAndAtomizerPower();
	updateShutdownTimeIfTimerEnabled();
}

void App::tick() {
	screenBuffer.clear(&Theme::black);
	menu.render();
	screenBuffer.flush();
	config.tick();

	readAtmosphericSensor();
	checkTargetHumidity();
	checkShutdownTime();

	// 30 FPS should be enough
	delay(1000 / 30);
}

void App::updateShutdownTime() {
	_shutdownTime = millis() + config.shutdownDelay * 60000;
//_shutdownTime = millis() + 5000;
}

void App::updateShutdownTimeIfTimerEnabled() {
	if (config.shutdownDelay > 0) {
		updateShutdownTime();
	}
	else {
		_shutdownTime = 0;
	}
}

void App::setFanOrAtomizerPower(uint8_t pin, uint8_t value) const {
	analogWriteFrequency(16000);
	analogWriteResolution(8);
	analogWrite(pin, _targetHumidityReached ? 0xFF : 0xFF - value);
}

void App::updateFanPower() {
	setFanOrAtomizerPower(constants::pinout::fan, config.fanPower);
}

void App::updateAtomizerPower() {
	setFanOrAtomizerPower(constants::pinout::atomizer, config.atomizerPower);
}

void App::updateFanAndAtomizerPower() {
	updateFanPower();
	updateAtomizerPower();
}

void App::checkTargetHumidity() {
	if (!isAtmosphericDataAvailable())
		return;

	if (_targetHumidityReached) {
		if (_humidity < (float) config.targetHumidity) {
			_targetHumidityReached = false;
			updateFanAndAtomizerPower();
		}
	}
	else {
		if (_humidity >= (float) (config.targetHumidity + constants::targetHumidityThreshold)) {
			_targetHumidityReached = true;
			updateFanAndAtomizerPower();
		}
	}
}

void App::checkShutdownTime() {
	if (config.shutdownDelay == 0)
		return;

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

void App::readAtmosphericSensor() {
	if (millis() < _atmosphericSensorTickTime)
		return;

	_humidity = atmosphericSensor.getHumidity();
	_temperature = atmosphericSensor.getTemperature();

//	Serial.printf("Humi, temp: %f, %f\n", _humidity, _temperature);

	_atmosphericSensorTickTime = millis() + atmosphericSensor.getMinimumSamplingPeriod();
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

bool App::isAtmosphericDataAvailable() const {
	return !isnan(_humidity) && !isnan(_temperature);
}
