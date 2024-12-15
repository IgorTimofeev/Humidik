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
	renderCenteredText(&Theme::fontBig, *getConfigValue() ? _trueText : _falseText);
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