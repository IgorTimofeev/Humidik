#include "Arduino.h"
#include "settings.h"
#include "ui/theme.h"
#include "../lib/YOBA/src/hardware/screen/drivers/SH1106Driver.h"
#include "../lib/YOBA/src/hardware/screen/buffers/monochromeBuffer.h"
#include <Adafruit_GFX.h>
#include <SH1106.h>
#include "ui/humidifier_application.h"

HumidifierApplication application = HumidifierApplication();

void setup() {
	Serial.begin(115200);

	application.setup();
}

void loop() {
	application.tick();

	delay(1);
}

// ----------------------------------------------------------------------
//
//using namespace yoba;
//
//SH1106Driver screenDriver = SH1106Driver(
//	settings::pinout::screen::chipSelect,
//	settings::pinout::screen::dataCommand,
//	settings::pinout::screen::reset
//);
//
//MonochromeBuffer screenBuffer = MonochromeBuffer(&screenDriver);
//
//void setup() {
//	Serial.begin(115200);
//
//	screenBuffer.setup();
//}
//
//void loop() {
//	screenBuffer.clear(&Theme::color1);
//	screenBuffer.renderFilledRectangle(Bounds(10, 10, 50, 20), &Theme::color2);
//	screenBuffer.renderHorizontalLine(Point(10, 40), 16, &Theme::color2);
//	screenBuffer.renderText(Point(10, 50), &Theme::font, &Theme::color2, "Penis");
//	screenBuffer.flush();
//
//	delay(2000);
//}

// ----------------------------------------------------------------------

//Adafruit_SH1106 display(
//	settings::pinout::screen::dataCommand,
//	settings::pinout::screen::reset,
//	settings::pinout::screen::chipSelect
//);
//
//void setup() {
//	Serial.begin(115200);
//
//	display.begin();
//}
//
//void loop() {
//	display.fillScreen(1);
//
//	display.fillRect(10, 10, 30, 20, 0);
//
//	display.display();
//
//	delay(2000);
//}