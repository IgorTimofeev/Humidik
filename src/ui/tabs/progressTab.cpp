#include "progressTab.h"
#include "ui/app.h"
#include "../../../lib/YOBA/src/number.h"

ProgressTab::ProgressTab(const wchar_t* name) : Tab(name) {

}

void ProgressTab::render() {
	auto& app = App::getInstance();

	const auto& bufferSize = app.screenBuffer.getSize();
	const auto& size = Size(80, 5);

	const auto& bounds = Bounds(
		Point(
			bufferSize.getWidth() / 2 - size.getWidth() / 2,
			bufferSize.getHeight() / 2 - size.getHeight() / 2
		),
		size
	);

	app.screenBuffer.renderHorizontalLine(Point(bounds.getX(), bounds.getYCenter()), bounds.getWidth(), &Theme::black);
	app.screenBuffer.renderFilledRectangle(
		Bounds(bounds.getX(), bounds.getY(), (uint16_t) ((float) bounds.getWidth() * _value),bounds.getHeight()),
		2,
		&Theme::black
	);

	// Text
	wchar_t textBuffer[4];
	swprintf(textBuffer, 4, L"%.0f%", _value * 100);
	app.screenBuffer.renderText(
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

void ProgressTab::onRotate() {
	auto& app = App::getInstance();

	const auto rotation = app.encoder.getRotation();

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

	app.encoder.setRotation(0);

	onValueChanged();

//	Serial.printf("Delta time: %lu, value: %f\n", deltaTime, _value);
}

void ProgressTab::onValueChanged() {

}

PWMProgressTab::PWMProgressTab(const wchar_t* name, uint8_t pin, uint8_t* configValue) : ProgressTab(name), _pin(pin), _configValue(configValue) {

}

void PWMProgressTab::setup() {
	setValue((float) *_configValue / 255.f);
	pwm();
}

void PWMProgressTab::onValueChanged() {
	_configValue[0] = (uint8_t) (getValue() * 255.f);

	pwm();

	App::getInstance().config.enqueueWrite();
}

void PWMProgressTab::pwm() const {
	analogWrite(_pin, 255 - *_configValue);
}