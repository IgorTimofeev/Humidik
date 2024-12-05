#include "menu.h"
#include "application.h"

void Menu::setup() {
	addTab(&_sensorsTab);
	addTab(&_colorsTab);
	addTab(&_powerTab);
}

void Menu::tick(Application* app) {
	auto display = app->getDisplay();
	auto encoder = app->getEncoder();

	if (abs(encoder.getRotation()) > 3) {
		_selectedIndex += encoder.getRotation() > 0 ? 1 : -1;

		encoder.setRotation(0);

		Serial.printf("Encoder rotation: %d\n", encoder.getRotation());

		if (_selectedIndex < 0) {
			_selectedIndex = 0;
		}
		else if (_selectedIndex > _tabs.size() - 1) {
			_selectedIndex = (int8_t) (_tabs.size() - 1);
		}
	}

	auto selectedTab = getSelectedTab();

	// Clearing display
	display->setDrawColor(1);
	display->drawBox(0, 0, display->getWidth(), display->getHeight());

	if (selectedTab) {
		// Drawing nav bar
		display->setDrawColor(0);

		const auto textWidth = display->getStrWidth(selectedTab->getName());
		const auto textHeight = display->getAscent() - display->getDescent();

		int32_t textX = display->getWidth() / 2 - textWidth / 2;
		int32_t textY = 2 + textHeight;

		// Tab name
		display->setCursor(textX, textY);
		display->setFont(u8g2_font_t0_14b_me);
		display->print(selectedTab->getName());

		// Dots
		const uint8_t dotSize = 2;
		const uint8_t dotSpacing = 5;
		const uint8_t dotOffset = 5;

		int32_t x = textX - dotOffset;
		int32_t y = textY - textHeight / 2;

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
