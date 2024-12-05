#include "tab.h"
#include "ui/application.h"

Tab::Tab(const char* name) : _name(name) {

}

void Tab::setup() {

}

void Tab::tick(Application* app) {

}

void Tab::render(Application* app) {
	auto display = app->getDisplay();


}

const char* Tab::getName() const {
	return _name;
}
