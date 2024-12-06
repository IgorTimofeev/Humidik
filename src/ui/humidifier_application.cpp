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
	_display.begin();
	_display.setFont(u8g2_font_logisoso20_tf);
	_display.clearBuffer();
	_display.sendBuffer();

	// Menu
	_menu.setup();
}

void HumidifierApplication::tick() {
	_menu.tick(this);
}

Encoder* HumidifierApplication::getEncoder() {
	return &_encoder;
}