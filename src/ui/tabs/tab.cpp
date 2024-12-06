#include "tab.h"
#include "ui/humidifier_application.h"

Tab::Tab(const char* name) : _name(name) {

}

void Tab::setup() {

}

void Tab::tick(HumidifierApplication* app) {

}

const char* Tab::getName() const {
	return _name;
}
