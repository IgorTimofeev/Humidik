#include "booleanTab.h"
#include "ui/app.h"
#include "../../../lib/YOBA/src/number.h"

BooleanTab::BooleanTab(const wchar_t* name, const wchar_t* trueText, const wchar_t* falseText, bool* configValue) :
	Tab(name),
	ConfigValueTab<bool>(configValue),
	_trueText(trueText),
	_falseText(falseText)
{

}

void BooleanTab::render() {
	auto& app = App::getInstance();

	const auto text = *getConfigValue() ? _trueText : _falseText;
	const auto& textSize = Theme::fontBig.getSize(text);

	app.screenBuffer.renderText(
		Point(
			app.screenBuffer.getSize().getWidth() / 2 - textSize.getWidth() / 2,
			app.screenBuffer.getSize().getHeight() / 2 - textSize.getHeight() / 2
		),
		&Theme::fontBig,
		&Theme::white,
		text
	);
}

void BooleanTab::onRotate() {
	auto& app = App::getInstance();

	if (abs(app.encoder.getRotation()) < 4)
		return;

	// Config
	*getConfigValue() = !*getConfigValue();
	app.config.enqueueWrite();

	app.encoder.setRotation(0);

	onRotateProcessed();
}