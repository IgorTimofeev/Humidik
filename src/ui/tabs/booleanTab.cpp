#include "booleanTab.h"
#include "ui/humidifierApplication.h"
#include "../../../lib/YOBA/src/number.h"

BooleanTab::BooleanTab(const wchar_t* name) : Tab(name) {

}

void BooleanTab::render(HumidifierApplication* app) {
	auto screenBuffer = app->getScreenBuffer();

	const auto text = _value ? L"Yes" : L"No";
	const auto& textSize = Theme::fontBig.getSize(text);

	screenBuffer->renderText(
		Point(
			screenBuffer->getSize().getWidth() / 2 - textSize.getWidth() / 2,
			screenBuffer->getSize().getHeight() / 2 - textSize.getHeight() / 2
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

void BooleanTab::onRotate(HumidifierApplication* app) {
	if (abs(app->getEncoder()->getRotation()) < 4)
		return;

	_value = app->getEncoder()->getRotation() > 0;
	app->getEncoder()->setRotation(0);

	onValueChanged(app);
}
