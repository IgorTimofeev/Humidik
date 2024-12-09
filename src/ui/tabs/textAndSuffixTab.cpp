#include "textAndSuffixTab.h"
#include "../app.h"

TextAndSuffixTab::TextAndSuffixTab(const wchar_t* name) : Tab(name) {

}

void TextAndSuffixTab::render() {
	if (!_text)
		return;

	auto& app = App::getInstance();
	const auto& bigSize = Theme::fontBig.getSize(_text);
	const uint8_t marginTop = 5;

	Point position = Point(
		app.screenBuffer.getSize().getWidth() / 2 - bigSize.getWidth() / 2,
		marginTop + (app.screenBuffer.getSize().getHeight() - marginTop) / 2 - bigSize.getHeight() / 2
	);

	app.screenBuffer.renderText(position, &Theme::fontBig, &Theme::white, _text);

	if (!_suffix)
		return;

	position.setX(position.getX() + bigSize.getWidth() + 2);
	position.setY(position.getY() + bigSize.getHeight() - Theme::fontSmall.getHeight() - 4);

	app.screenBuffer.renderText(position, &Theme::fontSmall, &Theme::white, _suffix);
}

wchar_t* TextAndSuffixTab::getText() const {
	return _text;
}

void TextAndSuffixTab::setText(wchar_t* text) {
	_text = text;
}

wchar_t* TextAndSuffixTab::getSuffix() const {
	return _suffix;
}

void TextAndSuffixTab::setSuffix(wchar_t* suffix) {
	_suffix = suffix;
}