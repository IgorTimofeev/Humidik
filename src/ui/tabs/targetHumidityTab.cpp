#include "shutdownTab.h"
#include "../app.h"
#include "../../../lib/YOBA/src/number.h"

TargetHumidityTab::TargetHumidityTab() : TextAndSuffixTab(L"Target"), ConfigValueTab<uint8_t>(&App::getInstance().config.targetHumidity) {
	setText(_textBuffer);

	wcscpy(_suffixBuffer, L"%");
	setSuffix(_suffixBuffer);
}

void TargetHumidityTab::setup() {
	updateTextBuffers();
}

void TargetHumidityTab::onRotate() {
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

	if (deltaTime < 60) {
		addend = 10;
	}
	else {
		addend = 1;
	}

	*getConfigValue() = addSaturating(*getConfigValue(), addend * (rotation > 0 ? 1 : -1));

	updateTextBuffers();

	// Config
	app.config.enqueueWrite();
}

void TargetHumidityTab::updateTextBuffers() {
	const auto value = *getConfigValue();

	swprintf(_textBuffer, 4, L"%d", value);
}
