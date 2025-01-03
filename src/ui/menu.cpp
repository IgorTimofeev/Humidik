#include "../../lib/YOBA/src/number.h"
#include "menu.h"
#include "app.h"
#include "ui/tabs/tab.h"
#include "ui/tabs/infoTab.h"
#include "ui/tabs/colorTabs.h"
#include "ui/tabs/fanTab.h"
#include "ui/tabs/atomizerTab.h"
#include "ui/tabs/contrastTab.h"
#include "ui/tabs/themeTab.h"
#include "ui/tabs/shutdownTab.h"
#include "ui/tabs/targetHumidityTab.h"
#include "array"

void Menu::setup() {
	uint8_t index = 0;

	const auto addTab = [&](Tab* tab) {
		tab->setup();
		_tabs[index] = tab;
		index++;
	};

	addTab(new InfoTab());
	addTab(new TargetHumidityTab());
	addTab(new ShutdownTab());
	addTab(new HueTab());

	addTab(new SaturationTab());
	addTab(new BrightnessTab());
	addTab(new AtomizerTab());
	addTab(new FanTab());

	addTab(new ContrastTab());
	addTab(new ThemeTab());
}

void Menu::render() {
	auto& app = App::getInstance();

	auto selectedTab = _tabs[app.config.ui.tabIndex];

	// No encoder press change detected
	if (app.encoder.isPressed() == _oldPressed) {
		// Rotating focused tab
		if (app.config.ui.focused) {
			selectedTab->onRotate();
		}
		// Cycling between tabs
		else {
			if (abs(app.encoder.getRotation()) > 3) {
				app.config.ui.tabIndex = (uint8_t) clamp(
					(int8_t) ((int8_t) app.config.ui.tabIndex + (app.encoder.getRotation() > 0 ? 1 : -1)),
					(int8_t) 0,
					(int8_t) (_tabs.size() - 1)
				);

				app.encoder.setRotation(0);

				selectedTab = _tabs[app.config.ui.tabIndex];

				app.config.enqueueWrite();
			}
		}
	}
	else {
		// Encoder press
		if (app.encoder.isPressed() && selectedTab->isFocusable()) {
			app.config.ui.focused = !app.config.ui.focused;

			app.config.enqueueWrite();
		}
	}

	_oldPressed = app.encoder.isPressed();

	// Rendering UI
	const auto textSize = Theme::fontSmall.getSize(selectedTab->getName());

	int32_t textX = app.screenBuffer.getSize().getXCenter() - textSize.getXCenter();
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
			&Theme::white
		);
	}

	// Text
	app.screenBuffer.renderText(
		Point(textX, textY),
		&Theme::fontSmall,
		app.config.ui.focused ? &Theme::black : &Theme::white,
		selectedTab->getName()
	);

	// Dots
	const uint8_t dotSpacing = 4;
	const uint8_t dotOffset = 3;

	int32_t x = textX - dotOffset;
	int32_t y = textY + textSize.getYCenter();

	// Left dots
	for (int32_t i = app.config.ui.tabIndex - 1; i >= 0; i--) {
		app.screenBuffer.renderPixel(Point(x - dotSpacing, y), &Theme::white);
		x = x - dotSpacing;
	}

	// Right dots
	x = textX + textSize.getWidth() + dotOffset;

	for (int32_t i = app.config.ui.tabIndex + 1; i < _tabs.size(); i++) {
		app.screenBuffer.renderPixel(Point(x, y), &Theme::white);
		x = x + dotSpacing;
	}

	// Tab content
	selectedTab->render();
}
