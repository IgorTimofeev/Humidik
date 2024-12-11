#include "infoTab.h"
#include "../app.h"

InfoTab::InfoTab() : Tab(L"Info") {
	setFocusable(false);

	wcscpy(_humiditySuffixBuffer, L"%");
	wcscpy(_temperatureSuffixBuffer, L"°C");
}

void InfoTab::render() {
	auto& app = App::getInstance();
	const auto& screenSize = app.screenBuffer.getSize();

	if (app.isAtmosphericDataAvailable()) {
		const uint8_t marginLine = 15;
		const uint8_t halfWidth = screenSize.getXCenter();

		swprintf(_humidityTextBuffer, 6, L"%.0f", app.getHumidity());
		swprintf(_temperatureTextBuffer, 6, L"%.0f", app.getTemperature());

		const auto renderPizda = [](const Bounds& bounds, int8_t marginLeft, wchar_t* text, wchar_t* suffix) {
			auto& app = App::getInstance();

//		app.screenBuffer.renderRectangle(bounds, &Theme::white);

			const auto& bigSize = Theme::fontBig.getSize(text);

			Point position = Point(
				bounds.getXCenter() - bigSize.getXCenter() + marginLeft,
				bounds.getYCenter() - bigSize.getYCenter()
			);

			app.screenBuffer.renderText(position, &Theme::fontBig, &Theme::white, text);

			position.setX(position.getX() + bigSize.getWidth() + 2);
			position.setY(position.getY() + bigSize.getHeight() - Theme::fontSmall.getHeight() - 4);

			app.screenBuffer.renderText(position, &Theme::fontSmall, &Theme::white, suffix);
		};

		// Left
		auto bounds = Bounds(
			0,
			App::marginTop,
			halfWidth,
			screenSize.getHeight() - App::marginTop
		);

		renderPizda(bounds, -1, _humidityTextBuffer, _humiditySuffixBuffer);

		// Line
		app.screenBuffer.renderVerticalLine(
			Point(halfWidth, App::marginTop + marginLine),
			bounds.getHeight() - marginLine * 2,
			&Theme::white
		);

		// Right
		bounds.setX(bounds.getX() + bounds.getWidth());
		renderPizda(bounds, -4, _temperatureTextBuffer, _temperatureSuffixBuffer);
	}
	else {
		const auto& text = L"IRS ALIGN";
		const auto& textSize = Theme::fontBig.getSize(text);

		app.screenBuffer.renderText(
			Point(
				screenSize.getXCenter() - textSize.getXCenter(),
				App::marginTop + (screenSize.getHeight() - App::marginTop) / 2 - textSize.getYCenter()
			),
			&Theme::fontBig,
			&Theme::white,
			text
		);
	}
}
