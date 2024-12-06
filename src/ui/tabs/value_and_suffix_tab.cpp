#include "value_and_suffix_tab.h"
#include "ui/humidifier_application.h"

ValueAndSuffixTab::ValueAndSuffixTab(const char* name) : Tab(name) {

}

void ValueAndSuffixTab::render(HumidifierApplication* app) {
	auto display = app->getDisplay();

	display->setFont(u8g2_font_logisoso22_tf);
	display->setFontPosTop();

	uint16_t textWidth = display->getStrWidth(value);
	uint16_t textHeight = display->getAscent() - display->getDescent();

	int32_t x = display->getWidth() / 2 - textWidth / 2;
	int32_t y = display->getHeight() / 2 - textHeight / 2;

	display->drawStr(x, y, value);

	display->setFont(u8g2_font_6x10_tf);
	display->setFontPosTop();

	x += textWidth + 3;
	y += textHeight;

	textHeight = display->getAscent() - display->getDescent();

	y = y - textHeight - 4;

	display->drawStr(x, y, suffix);
}
