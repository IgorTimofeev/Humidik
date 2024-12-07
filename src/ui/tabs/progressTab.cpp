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
	wchar_t textBuffer[5];
	swprintf(textBuffer, 5, L"%.0f%", _value * 100);
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
	_value = clamp(_value + (float) app->getEncoder()->getRotation() / 100.0f, 0.0f, 1.0f);
	app->getEncoder()->setRotation(0);
}
