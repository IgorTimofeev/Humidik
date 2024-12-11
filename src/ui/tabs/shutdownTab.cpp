#include "shutdownTab.h"
#include "../app.h"
#include "../../../lib/YOBA/src/number.h"

ShutdownTab::ShutdownTab() : TextAndSuffixTab(L"Timer"), ConfigValueTab<uint16_t>(&App::getInstance().config.shutdownDelay) {
	setText(_textBuffer);
}

void ShutdownTab::setup() {
	updateTextAndSuffixBuffers();
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

	if (app.config.shutdownDelay >= 60) {
		addend = rotation > 0 || app.config.shutdownDelay >= 120 ? 60 : 1;
		app.config.shutdownDelay = app.config.shutdownDelay - app.config.shutdownDelay % 60;
	}
	else {
		if (deltaTime < 60) {
			addend = 10;
		}
		else {
			addend = 1;
		}
	}

	app.config.shutdownDelay = addSaturating(app.config.shutdownDelay, addend * (rotation > 0 ? 1 : -1));
	app.updateShutdownTimeIfTimerEnabled();

	updateTextAndSuffixBuffers();

	// Config
	app.config.enqueueWrite();
}

void ShutdownTab::updateTextAndSuffixBuffers() {
	const auto value = *getConfigValue();

	if (value == 0) {
		wcscpy(_textBuffer, L"Disable");

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

void ShutdownTab::render() {
	TextAndSuffixTab::render();

//	auto& app = App::getInstance();
//
//	if (app.config.shutdownDelay == 0 || app.getShutdownTime() == 0)
//		return;
//
//	const auto totalSeconds = (app.getShutdownTime() - millis()) / 1000;
//	const uint8_t minutes = (totalSeconds / 60) % 60;
//	const uint8_t seconds = totalSeconds % 60;
//
//	const uint8_t footerBufferLength = 12;
//	wchar_t footerBuffer[footerBufferLength] {};
//
//	if (totalSeconds < 3600) {
//		swprintf(footerBuffer, footerBufferLength, L"%02d:%02d", minutes, seconds);
//	}
//	else {
//		const uint8_t hours = (totalSeconds / 3600) % 24;
//
//		swprintf(footerBuffer, footerBufferLength, L"%02d:%02d:%02d", hours, minutes, seconds);
//	}
//
//	const auto& screenSize = app.screenBuffer.getSize();
//	const auto& textSize = Theme::fontSmall.getSize(footerBuffer);
//
//	app.screenBuffer.renderText(
//		Point(
//			screenSize.getXCenter() - textSize.getXCenter(),
//			screenSize.getHeight() - textSize.getHeight()
//		),
//		&Theme::fontSmall,
//		&Theme::white,
//		footerBuffer
//	);
}
