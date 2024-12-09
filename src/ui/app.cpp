#include "app.h"
#include "EEPROM.h"

App& App::getInstance() {
	static App instance;

	return instance;
}

void App::setup() {
	// Config
	config.read();

	// Fan
	pinMode(constants::pinout::fan, OUTPUT);
	analogWriteFrequency(5000);
	analogWriteResolution(8);

//	ledcSetup(0, 312500, 8);
//	ledcAttachPin(settings::pinout::fan, 0);

	// Encoder
	encoder.setup();

	// Display
	screenBuffer.setup();

	// Menu
	menu.setup();
}

void App::tick() {
	menu.tick();
	config.tick();

	readSensors();
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
