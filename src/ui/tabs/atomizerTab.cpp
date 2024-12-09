#include "atomizerTab.h"
#include "../app.h"

AtomizerTab::AtomizerTab() : PWMProgressTab(L"Atomizer", constants::pinout::atomizer, &App::getInstance().config.atomizerPower) {

}