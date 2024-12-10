#include "progressTab.h"
#include "ui/app.h"
#include "../../../lib/YOBA/src/number.h"

ProgressTab::ProgressTab(const wchar_t* name, uint8_t* configValue) : Tab(name), ValueTab(), ConfigValueTab<uint8_t>(configValue) {

}

void ProgressTab::setup() {
	setValue((float) *getConfigValue() / 255.f);
}

void ProgressTab::onRotate() {
	auto& app = App::getInstance();

	const auto rotation = app.encoder.getRotation();

	if (abs(rotation) < 4)
		return;

	app.encoder.setRotation(0);

	// Value
	const auto time = millis();
	const auto deltaTime = time - _lastRotation;
	_lastRotation = time;

	float addend;

	if (deltaTime < 60) {
		addend = 0.10f;
	}
	else {
		addend = 0.01f;
	}

	setValue(clamp(getValue() + addend * (rotation > 0 ? 1.f : -1.f), 0.f, 1.f));

	// Config
	*getConfigValue() = (uint8_t) (getValue() * 255.f);
	app.config.enqueueWrite();

	onRotateProcessed();
}

void ProgressTab::render() {
	auto& app = App::getInstance();

	const auto& bufferSize = app.screenBuffer.getSize();
	const auto& size = Size(80, 5);

	const auto& bounds = Bounds(
		Point(
			bufferSize.getXCenter() - size.getXCenter(),
			bufferSize.getYCenter() - size.getYCenter()
		),
		size
	);

	app.screenBuffer.renderHorizontalLine(Point(bounds.getX(), bounds.getYCenter()), bounds.getWidth(), &Theme::white);
	app.screenBuffer.renderFilledRectangle(
		Bounds(bounds.getX(), bounds.getY(), (uint16_t) ((float) bounds.getWidth() * getValue()),bounds.getHeight()),
		2,
		&Theme::white
	);

	// Text
	wchar_t textBuffer[4];
	swprintf(textBuffer, 4, L"%.0f%", getValue() * 100);
	app.screenBuffer.renderText(
		Point(
			bounds.getXCenter() - Theme::fontSmall.getWidth(textBuffer) / 2,
			bounds.getY2() + 2
		),
		&Theme::fontSmall,
		&Theme::white,
		textBuffer
	);
}