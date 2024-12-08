#include "progressTab.h"
#include "ui/humidifierApplication.h"
#include "../../../lib/YOBA/src/number.h"

ProgressTab::ProgressTab(const wchar_t* name) : Tab(name) {

}

void ProgressTab::render(HumidifierApplication* app) {
	auto screenBuffer = app->getScreenBuffer();

	const auto& bufferSize = screenBuffer->getSize();
	const auto& size = Size(80, 5);

	const auto& bounds = Bounds(
		Point(
			bufferSize.getWidth() / 2 - size.getWidth() / 2,
			bufferSize.getHeight() / 2 - size.getHeight() / 2
		),
		size
	);

	screenBuffer->renderHorizontalLine(Point(bounds.getX(), bounds.getYCenter()), bounds.getWidth(), &Theme::black);
	screenBuffer->renderFilledRectangle(
		Bounds(bounds.getX(), bounds.getY(), (uint16_t) ((float) bounds.getWidth() * _value),bounds.getHeight()),
		2,
		&Theme::black
	);

	// Text
	wchar_t textBuffer[4];
	swprintf(textBuffer, 4, L"%.0f%", _value * 100);
	screenBuffer->renderText(
		Point(
			bounds.getXCenter() - Theme::fontSmall.getWidth(textBuffer) / 2,
			bounds.getY2() + 2
		),
		&Theme::fontSmall,
		&Theme::black,
		textBuffer
	);
}

float ProgressTab::getValue() const {
	return _value;
}

void ProgressTab::setValue(float value) {
	_value = value;
}

void ProgressTab::onRotate(HumidifierApplication* app) {
	const auto rotation = app->getEncoder()->getRotation();

	if (abs(rotation) < 4)
		return;

	const auto time = millis();
	const auto deltaTime = time -_lastRotation;

	float addend;

	if (deltaTime < 70) {
		addend = 0.10f;
	}
	else {
		addend = 0.01f;
	}

	_lastRotation = time;
	_value = clamp(_value + addend * (rotation > 0 ? 1.f : -1.f), 0.f, 1.f);

	app->getEncoder()->setRotation(0);

	onValueChanged(app);

//	Serial.printf("Delta time: %lu, value: %f\n", deltaTime, _value);
}
