#include "valueAndSuffixTab.h"
#include "ui/app.h"

ValueAndSuffixTab::ValueAndSuffixTab(const wchar_t* name) : Tab(name) {

}

void ValueAndSuffixTab::render() {
	auto& app = App::getInstance();

	auto textSize = Theme::fontBig.getSize(value);

	int32_t x = app.screenBuffer.getSize().getWidth() / 2 - textSize.getWidth() / 2;
	int32_t y = app.screenBuffer.getSize().getHeight() / 2 - textSize.getHeight() / 2;

	app.screenBuffer.renderText(Point(x, y), &Theme::fontBig, &Theme::black, value);

	x += textSize.getWidth() + 3;
	y += textSize.getHeight();

	y = y - Theme::fontSmall.getHeight();

	app.screenBuffer.renderText(Point(x, y), &Theme::fontSmall, &Theme::black, suffix);
}
