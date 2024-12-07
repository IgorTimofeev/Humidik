#include "fanTab.h"
#include "../humidifierApplication.h"

FanTab::FanTab() : ProgressTab(L"Fan") {
	setValue(1);
}

void FanTab::onRotate(HumidifierApplication* app) {
	ProgressTab::onRotate(app);


}
