#include "fanTab.h"
#include "../app.h"

FanTab::FanTab() : PWMProgressTab(L"Fan", constants::pinout::fan, &App::getInstance().config.fanPower) {

}