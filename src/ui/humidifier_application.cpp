#include "humidifier_application.h"

void HumidifierApplication::setup() {
	SPI.begin();

	// Pins
	pinMode(32, INPUT_PULLUP);
	pinMode(33, INPUT_PULLUP);
	pinMode(34, INPUT_PULLUP);

	// Encoder
	_encoder.setup();

	// Display
	_display.setup();

	// Menu
	_menu.setup();
}

void HumidifierApplication::tick() {
	_menu.tick(this);
}

Encoder* HumidifierApplication::getEncoder() {
	return &_encoder;
}

MonochromeBuffer* HumidifierApplication::getDisplay() {
	return &_display;
}
