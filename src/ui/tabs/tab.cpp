#include "tab.h"
#include "ui/app.h"

Tab::Tab(const wchar_t* name) : _name(name) {

}

void Tab::setup() {

}

void Tab::tick() {

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