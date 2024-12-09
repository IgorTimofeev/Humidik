#include "colorTabs.h"
#include "../app.h"

ColorTab::ColorTab(const wchar_t* name, uint8_t* configValue) : ProgressTab(name, configValue) {

}

HueTab::HueTab() : ColorTab(L"Hue", &App::getInstance().config.strip.hue) {

}

SaturationTab::SaturationTab() : ColorTab(L"Saturation", &App::getInstance().config.strip.saturation) {

}

BrightnessTab::BrightnessTab() : ColorTab(L"Brightness", &App::getInstance().config.strip.brightness) {

}