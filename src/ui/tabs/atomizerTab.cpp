#include "atomizerTab.h"
#include "../app.h"

AtomizerTab::AtomizerTab() : ProgressTab(L"Atomizer", &App::getInstance().config.atomizerPower) {

}

void AtomizerTab::onRotateProcessed() {
	ProgressTab::onRotateProcessed();

	App::getInstance().updateFanPower();
}