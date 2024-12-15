#include "tab.h"
#include "ui/app.h"

Tab::Tab(const wchar_t* name) : _name(name) {

}

void Tab::setup() {

}

const wchar_t* Tab::getName() const {
	return _name;
}

bool Tab::isFocusable() const {
	return _focusable;
}

void Tab::setFocusable(bool selectable) {
	_focusable = selectable;
}

void Tab::onRotate() {

}

void Tab::onRotateProcessed() {

}

void Tab::renderCenteredText(const Font* font, const wchar_t* text) {
	auto& app = App::getInstance();

	const auto& screenSize = app.screenBuffer.getSize();
	const auto& textSize = font->getSize(text);

	app.screenBuffer.renderText(
		Point(
			screenSize.getXCenter() - textSize.getXCenter(),
			App::marginTop + (screenSize.getHeight() - App::marginTop) / 2  - textSize.getYCenter()
		),
		font,
		&Theme::white,
		text
	);
}
