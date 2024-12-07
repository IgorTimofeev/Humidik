#include "menu.h"
#include "humidifierApplication.h"
#include "../../lib/YOBA/src/number.h"

void Menu::setup() {
	addTab(&_humidityTab);
	addTab(&_temperatureTab);
	addTab(&_hueTab);
	addTab(&_saturationTab);
	addTab(&_brightnessTab);
	addTab(&_fanTab);
	addTab(&_emitterTab);
	addTab(&_contrastTab);
	addTab(&_inversionTab);
}

void Menu::tick(HumidifierApplication* app) {
	auto screenBuffer = app->getScreenBuffer();
	auto encoder = app->getEncoder();

	// Rotation check
	auto selectedTab = getSelectedTab();

	if (encoder->getRotation() != 0) {
		// Using tab rotate
		if (selectedTab->isSelected()) {
			selectedTab->onRotate(app);
		}
		// Cycling between tabs
		else {
			if (abs(encoder->getRotation()) > 3) {
				_selectedIndex = (uint8_t) clamp(
					(int8_t) ((int8_t) _selectedIndex + (encoder->getRotation() > 0 ? 1 : -1)),
					(int8_t) 0,
					(int8_t) (_tabs.size() - 1)
				);

				selectedTab = getSelectedTab();

				encoder->setRotation(0);
			}
		}
	}

	// Press check
	bool pressedChanged = encoder->isPressed() != _oldPressed;
	_oldPressed = encoder->isPressed();

	// Toggling tab active state on encoder press
	if (pressedChanged && encoder->isPressed() && selectedTab->isSelectable()) {
		selectedTab->setSelected(!selectedTab->isSelected());
	}

	// Tab rendering
	screenBuffer->clear(&Theme::white);

	const auto textSize = Theme::fontSmall.getSize(selectedTab->getName());

	int32_t textX = screenBuffer->getSize().getWidth() / 2 - textSize.getWidth() / 2;
	int32_t textY = 2;

	// Border around selected tab
	if (selectedTab->isSelected()) {
		screenBuffer->renderFilledRectangle(
			Bounds(
				textX - 2,
				textY + 1,
				textSize.getWidth() + 2 * 2 - 1,
				textSize.getHeight() - 2
			),
			2,
			&Theme::black
		);
	}

	// Text
	screenBuffer->renderText(Point(textX, textY), &Theme::fontSmall, selectedTab->isSelected() ? &Theme::white : &Theme::black, selectedTab->getName());

	// Dots
	const uint8_t dotSize = 2;
	const uint8_t dotSpacing = 4;
	const uint8_t dotOffset = 4;

	int32_t x = textX - dotOffset;
	int32_t y = textY + textSize.getHeight() / 2;

	// Left dots
	for (int32_t i = _selectedIndex - 1; i >= 0; i--) {
		screenBuffer->renderRectangle(Bounds(x - dotSpacing, y, dotSize, dotSize), &Theme::black);
		x = x - dotSize - dotSpacing;
	}

	// Right dots
	x = textX + textSize.getWidth() + dotOffset;

	for (int32_t i = _selectedIndex + 1; i < _tabs.size(); i++) {
		screenBuffer->renderRectangle(Bounds(x, y, dotSize, dotSize), &Theme::black);
		x = x + dotSize + dotSpacing;
	}

	selectedTab->tick(app);
	selectedTab->render(app);

	screenBuffer->flush();
}

uint8_t Menu::getSelectedIndex() const {
	return _selectedIndex;
}

void Menu::setSelectedIndex(uint8_t value) {
	Menu::_selectedIndex = value;
}

Tab* Menu::getSelectedTab() {
	return _selectedIndex < _tabs.size() ? _tabs[_selectedIndex] : nullptr;
}

void Menu::addTab(Tab* tab) {
	_tabs.push_back(tab);
}
