#include "menu.h"
#include "app.h"
#include "../../lib/YOBA/src/number.h"
#include "array"

void Menu::setup() {
	switchTab();
}

void Menu::switchTab() {
	auto& app = App::getInstance();

	delete _selectedTab;

	_selectedTab = _tabs[app.config.ui.tabIndex]();
	_selectedTab->setup();
}

void Menu::tick() {
	auto& app = App::getInstance();

	// Pressing check
	if (app.encoder.getRotation() == 0) {
		bool pressedChanged = app.encoder.isPressed() != _oldPressed;
		_oldPressed = app.encoder.isPressed();

		// Toggling tab active state on encoder press
		if (pressedChanged && app.encoder.isPressed() && _selectedTab->isFocusable()) {
			app.config.ui.focused = !app.config.ui.focused;

			app.config.enqueueWrite();
		}
	}
	// Rotation check
	else {
		// Using tab rotate
		if (app.config.ui.focused) {
			_selectedTab->onRotate();
		}
		// Cycling between tabs
		else {
			if (abs(app.encoder.getRotation()) > 3) {
				app.config.ui.tabIndex = (uint8_t) clamp(
					(int8_t) ((int8_t) app.config.ui.tabIndex + (app.encoder.getRotation() > 0 ? 1 : -1)),
					(int8_t) 0,
					(int8_t) (_tabs.size() - 1)
				);

				switchTab();

				app.encoder.setRotation(0);

				app.config.enqueueWrite();
			}
		}
	}

	// Tab rendering
	app.screenBuffer.clear(&Theme::white);

	const auto textSize = Theme::fontSmall.getSize(_selectedTab->getName());

	int32_t textX = app.screenBuffer.getSize().getWidth() / 2 - textSize.getWidth() / 2;
	int32_t textY = 2;

	// Border around selected tab
	if (app.config.ui.focused) {
		app.screenBuffer.renderFilledRectangle(
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
	app.screenBuffer.renderText(
		Point(textX, textY),
		&Theme::fontSmall,
		app.config.ui.focused ? &Theme::white : &Theme::black,
		_selectedTab->getName()
	);

	// Dots
	const uint8_t dotSize = 2;
	const uint8_t dotSpacing = 4;
	const uint8_t dotOffset = 4;

	int32_t x = textX - dotOffset;
	int32_t y = textY + textSize.getHeight() / 2;

	// Left dots
	for (int32_t i = app.config.ui.tabIndex - 1; i >= 0; i--) {
		app.screenBuffer.renderRectangle(Bounds(x - dotSpacing, y, dotSize, dotSize), &Theme::black);
		x = x - dotSize - dotSpacing;
	}

	// Right dots
	x = textX + textSize.getWidth() + dotOffset;

	for (int32_t i = app.config.ui.tabIndex + 1; i < _tabs.size(); i++) {
		app.screenBuffer.renderRectangle(Bounds(x, y, dotSize, dotSize), &Theme::black);
		x = x + dotSize + dotSpacing;
	}

	_selectedTab->tick();
	_selectedTab->render();

	app.screenBuffer.flush();
}
