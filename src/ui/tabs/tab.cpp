#include "tab.h"
#include "ui/humidifier_application.h"

Tab::Tab(const wchar_t* name) : _name(name) {

}

void Tab::setup() {

}

void Tab::tick(HumidifierApplication* app) {

}

const wchar_t* Tab::getName() const {
	return _name;
}
