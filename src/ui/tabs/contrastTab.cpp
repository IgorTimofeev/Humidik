#include "contrastTab.h"
#include "../humidifierApplication.h"

ContrastTab::ContrastTab() : ProgressTab(L"CTRS") {
	setValue(1);
}

void ContrastTab::onRotate(HumidifierApplication* app) {
	ProgressTab::onRotate(app);

	app->getScreenDriver()->setContrast((uint8_t) (255.0f * getValue()));
}
