#include "booleanTab.h"
#include "ui/app.h"
#include "../../../lib/YOBA/src/number.h"

BooleanTab::BooleanTab(const wchar_t* name) : Tab(name) {

}

void BooleanTab::render() {
	auto& app = App::getInstance();

	const auto text = _value ? L"Yes" : L"No";
	const auto& textSize = Theme::fontBig.getSize(text);

	app.screenBuffer.renderText(
		Point(
			app.screenBuffer.getSize().getWidth() / 2 - textSize.getWidth() / 2,
			app.screenBuffer.getSize().getHeight() / 2 - textSize.getHeight() / 2
		),
		&Theme::fontBig,
		&Theme::black,
		text
	);
}

bool BooleanTab::getValue() const {
	return _value;
}

void BooleanTab::setValue(bool value) {
	_value = value;
}

void BooleanTab::onRotate() {
	auto& app = App::getInstance();

	if (abs(app.encoder.getRotation()) < 4)
		return;

	_value = app.encoder.getRotation() > 0;
	app.encoder.setRotation(0);

	onValueChangedByRotate();
}

void BooleanTab::onValueChangedByRotate() {

}
