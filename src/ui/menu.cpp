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
	display->clear(&Theme::white);

	if (selectedTab) {
		const auto textSize = Theme::fontSmall.getSize(selectedTab->getName());

		int32_t textX = display->getSize().getWidth() / 2 - textSize.getWidth() / 2;
		int32_t textY = 2;

		display->renderText(Point(textX, textY), &Theme::fontSmall, &Theme::black, selectedTab->getName());

		// Dots
		const uint8_t dotSize = 2;
		const uint8_t dotSpacing = 5;
		const uint8_t dotOffset = 5;

		int32_t x = textX - dotOffset;
		int32_t y = textY + textSize.getHeight() / 2;

		// Left dots
		for (int32_t i = _selectedIndex - 1; i >= 0; i--) {
			display->renderRectangle(Bounds(x - dotSpacing, y, dotSize, dotSize), &Theme::black);
			x = x - dotSize - dotSpacing;
		}

		// Right dots
		x = textX + textSize.getWidth() + dotOffset;

		for (int32_t i = _selectedIndex + 1; i < _tabs.size(); i++) {
			display->renderRectangle(Bounds(x, y, dotSize, dotSize), &Theme::black);
			x = x + dotSize + dotSpacing;
		}

		selectedTab->tick(app);
		selectedTab->render(app);
	}

	display->flush();
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
