#include "fanTab.h"
#include "../app.h"

FanTab::FanTab() : ProgressTab(L"Fan", &App::getInstance().config.fanPower) {

}

void FanTab::onRotateProcessed() {
	ProgressTab::onRotateProcessed();

	App::getInstance().updateFanPower();
}