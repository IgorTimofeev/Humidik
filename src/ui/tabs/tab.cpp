#include "tab.h"
#include "ui/application.h"

Tab::Tab(const char* name) : _name(name) {

}

void Tab::setup() {

}

void Tab::tick(Application* app) {

}

const char* Tab::getName() const {
	return _name;
}
