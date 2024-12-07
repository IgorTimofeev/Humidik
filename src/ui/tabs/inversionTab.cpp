#include "inversionTab.h"
#include "../humidifierApplication.h"

InversionTab::InversionTab() : BooleanTab(L"INV") {

}

void InversionTab::onRotate(HumidifierApplication* app) {
	BooleanTab::onRotate(app);

	app->getScreenDriver()->setInverted(getValue());
}
