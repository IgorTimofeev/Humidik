#include "themeTab.h"
#include "../app.h"

ThemeTab::ThemeTab() : BooleanTab(L"Theme", L"Bright", L"Dark", &App::getInstance().config.display.invert) {

}

void ThemeTab::setup() {
	updateDriver();
}

void ThemeTab::onRotateProcessed() {
	updateDriver();
}

void ThemeTab::updateDriver() {
	App::getInstance().screenDriver.setInverted(*getConfigValue());
}