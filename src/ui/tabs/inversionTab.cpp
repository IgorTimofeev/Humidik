#include "inversionTab.h"
#include "../app.h"

InversionTab::InversionTab() : BooleanTab(L"INV") {

}

void InversionTab::onValueChangedByRotate() {
	App::getInstance().screenDriver.setInverted(getValue());
}
