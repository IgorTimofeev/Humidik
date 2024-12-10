#include "app.h"
#include "EEPROM.h"
#include "../../lib/YOBA/src/number.h"

App& App::getInstance() {
	static App instance;

	return instance;
}

void App::setup() {
	// Config
	config.read();

	// GPIO
	pinMode(constants::pinout::fan, OUTPUT);
	pinMode(constants::pinout::atomizer, OUTPUT);

	// Encoder
	encoder.setup();

	// Screen
	screenBuffer.setup();

	// UI
	menu.setup();

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

			if (_shutdownState) {
				_shutdownState = false;
				updateFanAndAtomizerPower();
			}
		}
		else {
			if (millis() >= _shutdownTime) {
				_shutdownState = true;
				_shutdownTime = 0;

				updateFanAndAtomizerPower();
			}
		}
	}

	screenBuffer.flush();

	config.tick();
}

void App::updateShutdownTime() {
	_shutdownTime = millis() + config.shutdownDelay * 60000;
}

void App::updateShutdownTimeConditional() {
	if (config.shutdownDelay > 0) {
		updateShutdownTime();
	}
	else {
		_shutdownTime = 0;
	}
}

void App::analogWriteToDevice(uint8_t pin, uint8_t value) const {
	analogWriteFrequency(16000);
	analogWriteResolution(8);
	analogWrite(pin, _shutdownState ? 0xFF : 0xFF - value);
}

void App::updateFanPower() {
	analogWriteToDevice(constants::pinout::fan, config.fanPower);
}

void App::updateAtomizerPower() {
	analogWriteToDevice(constants::pinout::atomizer, config.atomizerPower);
}

void App::updateFanAndAtomizerPower() {
	updateFanPower();
	updateAtomizerPower();
}

void App::readSensors() {
	if (millis() < _sensorsTickDeadline)
		return;

	_humidity = (float) random(40, 50);
	_temperature = (float) random(24, 30);

	_sensorsTickDeadline = millis() + 1000;
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
