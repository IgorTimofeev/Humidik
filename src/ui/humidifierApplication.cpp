#include "humidifierApplication.h"

void HumidifierApplication::setup() {
	SPI.begin();

	// Pins
	pinMode(32, INPUT_PULLUP);
	pinMode(33, INPUT_PULLUP);
	pinMode(34, INPUT_PULLUP);

	// Fan
	pinMode(settings::pinout::fan, OUTPUT);
	analogWriteFrequency(5000);
	analogWriteResolution(8);

//	ledcSetup(0, 312500, 8);
//	ledcAttachPin(settings::pinout::fan, 0);

	// Encoder
	_encoder.setup();

	// Display
	_screenBuffer.setup();

	// Menu
	_menu.setup();
}

void HumidifierApplication::tick() {
	_menu.tick(this);
}

Encoder* HumidifierApplication::getEncoder() {
	return &_encoder;
}

MonochromeBuffer* HumidifierApplication::getScreenBuffer() {
	return &_screenBuffer;
}

SH1106Driver* HumidifierApplication::getScreenDriver() {
	return &_screenDriver;
}
