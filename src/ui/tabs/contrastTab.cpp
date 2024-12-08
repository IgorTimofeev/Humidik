#include "contrastTab.h"
#include "../app.h"

ContrastTab::ContrastTab() : ProgressTab(L"CTRS") {

}

void ContrastTab::onValueChanged() {
	App::getInstance().screenDriver.setContrast((uint8_t) (255.0f * getValue()));
}
