#include "Arduino.h"
#include "ui/app.h"

App& application = App::getInstance();

void setup() {
	Serial.begin(115200);

	application.setup();
}

void loop() {
	application.tick();

	delay(16);
}