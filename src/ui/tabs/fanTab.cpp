#include "fanTab.h"
#include "../humidifierApplication.h"

FanTab::FanTab() : ProgressTab(L"Fan") {

}

void FanTab::onValueChanged(HumidifierApplication* app) {
	const auto pwmValue = (uint8_t) ((1.f - getValue()) * 255.f);

	Serial.printf("PWM value: %d\n", pwmValue);

	analogWrite(settings::pinout::fan, pwmValue);
//	ledcWrite(0, pwmValue);
}
