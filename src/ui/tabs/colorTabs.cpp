#include "colorTabs.h"
#include "../humidifierApplication.h"

ColorTab::ColorTab(const wchar_t* name) : ProgressTab(name) {

}

HueTab::HueTab() : ColorTab(L"HUE") {

}

SaturationTab::SaturationTab() : ColorTab(L"SAT") {

}

BrightnessTab::BrightnessTab() : ColorTab(L"BRT") {

}
