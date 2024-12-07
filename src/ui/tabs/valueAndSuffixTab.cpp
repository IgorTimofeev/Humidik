#include "valueAndSuffixTab.h"
#include "ui/humidifierApplication.h"

ValueAndSuffixTab::ValueAndSuffixTab(const wchar_t* name) : Tab(name) {

}

void ValueAndSuffixTab::render(HumidifierApplication* app) {
	auto screenBuffer = app->getScreenBuffer();

	auto textSize = Theme::fontBig.getSize(value);

	int32_t x = screenBuffer->getSize().getWidth() / 2 - textSize.getWidth() / 2;
	int32_t y = screenBuffer->getSize().getHeight() / 2 - textSize.getHeight() / 2;

	screenBuffer->renderText(Point(x, y), &Theme::fontBig, &Theme::black, value);

	x += textSize.getWidth() + 3;
	y += textSize.getHeight();

	y = y - Theme::fontSmall.getHeight();

	screenBuffer->renderText(Point(x, y), &Theme::fontSmall, &Theme::black, suffix);
}
