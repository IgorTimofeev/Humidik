//#include "Arduino.h"
//#include "ui/humidifier_application.h"
//HumidifierApplication application = HumidifierApplication();

//void setup() {
//	Serial.begin(115200);
//
//	application.setup();
//}
//
//void loop() {
//	application.tick();
//
//	delay(1);
//}

#include "Arduino.h"
#include "settings.h"
#include "ui/theme.h"
#include "../lib/YOBA/src/hardware/screen/drivers/SH1106Driver.h"
#include "../lib/YOBA/src/hardware/screen/buffers/monochromeBuffer.h"

using namespace yoba;

SH1106Driver screenDriver = SH1106Driver(
	ScreenOrientation::Clockwise0,
	Size(128, 64),
	settings::pinout::screen::chipSelect,
	settings::pinout::screen::dataCommand,
	settings::pinout::screen::reset
);

MonochromeBuffer screenBuffer = MonochromeBuffer(&screenDriver);

void setup() {
	Serial.begin(115200);

	screenBuffer.setup();
}

void loop() {
	const auto bounds = Bounds(Point(0, 0), screenDriver.getResolution());

	screenBuffer.clear(&Theme::color1);
//	screenBuffer.renderFilledRectangle(bounds, &Theme::color1);
//	screenBuffer.renderFilledRectangle(Bounds(10, 10, 10, 10), &Theme::color2);

//	screenBuffer.renderText(Point(10, 10), &Theme::font, &Theme::color2, "Penis");
	screenBuffer.flush();

	delay(2000);
}