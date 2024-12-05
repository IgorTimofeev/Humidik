#include "application.h"

void Application::setup() {
	SPI.begin();

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

void Application::tick() {
	_menu.tick(this);
}

Encoder& Application::getEncoder() {
	return _encoder;
}
