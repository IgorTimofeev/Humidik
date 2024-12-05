#include "Arduino.h"
#include "ui/application.h"

Application application = Application();

void setup() {
	Serial.begin(115200);

	application.setup();
}

void loop() {
	application.tick();

	delay(1);
}