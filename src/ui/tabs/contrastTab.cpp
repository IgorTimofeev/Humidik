#include "contrastTab.h"
#include "../app.h"

ContrastTab::ContrastTab() : ProgressTab(L"Contrast", &App::getInstance().config.display.contrast) {

}

void ContrastTab::setup() {
	ProgressTab::setup();

	updateContrast();
}

void ContrastTab::onRotateProcessed() {
	updateContrast();
}

void ContrastTab::updateContrast() {
	App::getInstance().screenDriver.setContrast((uint8_t) (255.0f * getValue()));
}