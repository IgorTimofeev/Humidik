#include "contrastTab.h"
#include "../humidifierApplication.h"

ContrastTab::ContrastTab() : ProgressTab(L"CTRS") {

}

void ContrastTab::onValueChanged(HumidifierApplication* app) {
	app->getScreenDriver()->setContrast((uint8_t) (255.0f * getValue()));
}
