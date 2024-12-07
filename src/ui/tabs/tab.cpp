#include "tab.h"
#include "ui/humidifierApplication.h"

Tab::Tab(const wchar_t* name) : _name(name) {

}

void Tab::setup() {

}

void Tab::tick(HumidifierApplication* app) {

}

const wchar_t* Tab::getName() const {
	return _name;
}

bool Tab::isSelected() const {
	return _active;
}

void Tab::setSelected(bool value) {
	_active = value;
}

bool Tab::isSelectable() const {
	return _selectable;
}

void Tab::setSelectable(bool selectable) {
	_selectable = selectable;
}

void Tab::onRotate(HumidifierApplication* app) {

}