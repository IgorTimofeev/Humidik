#include "emitterTab.h"
#include "../humidifierApplication.h"

EmitterTab::EmitterTab() : ProgressTab(L"EMI") {
	setValue(1);
}

void EmitterTab::onRotate(HumidifierApplication* app) {
	ProgressTab::onRotate(app);

	
}
