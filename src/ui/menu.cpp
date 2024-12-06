#include "menu.h"
#include "humidifier_application.h"

void Menu::setup() {
	addTab(&_temperatureTab);
	addTab(&_humidityTab);
	addTab(&_colorsTab);
	addTab(&_powerTab);

	_selectedIndex = 0;
}

void Menu::tick(HumidifierApplication* app) {
	auto display = app->getDisplay();
	auto encoder = app->getEncoder();

	if (abs(encoder->getRotation()) > 3) {
		_selectedIndex += encoder->getRotation() > 0 ? 1 : -1;

		encoder->setRotation(0);

		if (_selectedIndex < 0) {
			_selectedIndex = 0;
		}
		else if (_selectedIndex > _tabs.size() - 1) {
			_selectedIndex = (int8_t) (_tabs.size() - 1);
		}
	}

	auto selectedTab = getSelectedTab();

	// Clearing display
	display->clearBuffer();
	display->setDrawColor(1);
	display->drawBox(0, 0, display->getWidth(), display->getHeight());

	if (selectedTab) {
		// Drawing nav bar
		display->setDrawColor(0);

		// Tab name
		display->setFont(u8g2_font_t0_11b_tf);
		display->setFontPosTop();

		const auto textWidth = display->getStrWidth(selectedTab->getName());
		const auto textHeight = display->getAscent() - display->getDescent();

		int32_t textX = display->getWidth() / 2 - textWidth / 2;
		int32_t textY = 2;

		display->drawStr(textX, textY, selectedTab->getName());

		// Dots
		const uint8_t dotSize = 2;
		const uint8_t dotSpacing = 5;
		const uint8_t dotOffset = 5;

		int32_t x = textX - dotOffset;
		int32_t y = textY + textHeight / 2;

		// Left dots
		for (int32_t i = _selectedIndex - 1; i >= 0; i--) {
			display->drawBox(x - dotSpacing, y, dotSize, dotSize);
			x = x - dotSize - dotSpacing;
		}

		// Right dots
		x = textX + textWidth + dotOffset;

		for (int32_t i = _selectedIndex + 1; i < _tabs.size(); i++) {
			display->drawBox(x, y, dotSize, dotSize);
			x = x + dotSize + dotSpacing;
		}

		selectedTab->tick(app);
		selectedTab->render(app);
	}

	display->sendBuffer();
}

int8_t Menu::getSelectedIndex() const {
	return _selectedIndex;
}

void Menu::setSelectedIndex(int8_t value) {
	Menu::_selectedIndex = value;
}

Tab* Menu::getSelectedTab() {
	return _selectedIndex >= 0 && _selectedIndex < _tabs.size() ? _tabs[_selectedIndex] : nullptr;
}
