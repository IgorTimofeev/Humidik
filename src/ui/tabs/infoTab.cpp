#include "infoTab.h"
#include "../app.h"

InfoTab::InfoTab() : Tab(L"Info") {
	setFocusable(false);

	wcscpy(_humiditySuffixBuffer, L"°C");
	wcscpy(_temperatureSuffixBuffer, L"°C");
}

void InfoTab::tick() {
	swprintf(_humidityTextBuffer, 16, L"%d", 60);
	swprintf(_temperatureTextBuffer, 16, L"%d", 24);
}

void InfoTab::render() {
	auto& app = App::getInstance();

	const auto renderPizda = [](const Bounds& bounds, int8_t marginLeft, wchar_t* text, wchar_t* suffix) {
		auto& app = App::getInstance();

//		app.screenBuffer.renderRectangle(bounds, &Theme::white);

		const auto& bigSize = Theme::fontBig.getSize(text);

		Point position = Point(
			bounds.getXCenter() - bigSize.getWidth() / 2 + marginLeft,
			bounds.getYCenter() - bigSize.getHeight() / 2
		);

		app.screenBuffer.renderText(position, &Theme::fontBig, &Theme::white, text);

		position.setX(position.getX() + bigSize.getWidth() + 2);
		position.setY(position.getY() + bigSize.getHeight() -  Theme::fontSmall.getHeight() - 4);

		app.screenBuffer.renderText(position, &Theme::fontSmall, &Theme::white, suffix);
	};

	const uint8_t marginTop = 5;
	const uint8_t marginLine = 15;
	const uint8_t halfWidth = app.screenBuffer.getSize().getWidth() / 2;

	// Left
	Bounds bounds = Bounds(
		0,
		marginTop,
		halfWidth,
		app.screenBuffer.getSize().getHeight() - marginTop
	);

	renderPizda(bounds, -3, _humidityTextBuffer, _humiditySuffixBuffer);

	// Line
	app.screenBuffer.renderVerticalLine(
		Point(halfWidth, marginTop + marginLine),
		bounds.getHeight() - marginLine * 2,
		&Theme::white
	);

	// Right
	bounds.setX(bounds.getX() + bounds.getWidth());
	renderPizda(bounds, -4, _temperatureTextBuffer, _temperatureSuffixBuffer);
}
