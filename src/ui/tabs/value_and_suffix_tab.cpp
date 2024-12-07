#include "value_and_suffix_tab.h"
#include "ui/humidifier_application.h"

ValueAndSuffixTab::ValueAndSuffixTab(const wchar_t* name) : Tab(name) {

}

void ValueAndSuffixTab::render(HumidifierApplication* app) {
	auto display = app->getDisplay();

	auto textSize = Theme::fontBig.getSize(value);

	int32_t x = display->getSize().getWidth() / 2 - textSize.getWidth() / 2;
	int32_t y = display->getSize().getHeight() / 2 - textSize.getHeight() / 2;

	display->renderText(Point(x, y), &Theme::fontBig, &Theme::black, value);

	x += textSize.getWidth() + 3;
	y += textSize.getHeight();

	y = y - Theme::fontSmall.getHeight();

	display->renderText(Point(x, y), &Theme::fontSmall, &Theme::black, suffix);
}
