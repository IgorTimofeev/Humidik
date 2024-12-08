#include "inversionTab.h"
#include "../humidifierApplication.h"

InversionTab::InversionTab() : BooleanTab(L"INV") {

}

void InversionTab::onValueChanged(HumidifierApplication* app) {
	app->getScreenDriver()->setInverted(getValue());
}
