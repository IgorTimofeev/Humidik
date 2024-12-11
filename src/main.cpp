#include "Arduino.h"
#include "ui/app.h"

App& application = App::getInstance();

void setup() {
	application.setup();
}

void loop() {
	application.tick();
}