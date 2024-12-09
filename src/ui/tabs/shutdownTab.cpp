#include "shutdownTab.h"
#include "../app.h"
#include "../../../lib/YOBA/src/number.h"

ShutdownTab::ShutdownTab() : TextAndSuffixTab(L"Shutdown"), ConfigValueTab<uint16_t>(&App::getInstance().config.shutdownDelay) {
	setText(_textBuffer);
}

void ShutdownTab::setup() {
	updateTextBuffers();
}

void ShutdownTab::onRotate() {
	auto& app = App::getInstance();

	const auto rotation = app.encoder.getRotation();

	if (abs(rotation) < 4)
		return;

	app.encoder.setRotation(0);

	// Value
	const auto time = millis();
	const auto deltaTime = time - _lastRotation;
	_lastRotation = time;

	int16_t addend;

	if (*getConfigValue() >= 60 && (rotation > 0 || *getConfigValue() >= 120)) {
		addend = 60;
	}
	else {
		if (deltaTime < 60) {
			addend = 10;
		}
		else {
			addend = 1;
		}
	}

	*getConfigValue() = addSaturating(*getConfigValue(), addend * (rotation > 0 ? 1 : -1));

	updateTextBuffers();

	// Config
	app.config.enqueueWrite();
}

void ShutdownTab::updateTextBuffers() {
	const auto value = *getConfigValue();

	if (value == 0) {
		wcscpy(_textBuffer, L"Disabled");

		setSuffix(nullptr);
	}
	else {
		if (value >= 60) {
			swprintf(_textBuffer, 16, L"%d", value / 60);

			wcscpy(_suffixBuffer, L"h");
		}
		else {
			swprintf(_textBuffer, 16, L"%d", value);

			wcscpy(_suffixBuffer, L"min");
		}

		setSuffix(_suffixBuffer);
	}
}
