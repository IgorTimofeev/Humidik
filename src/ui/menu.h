#pragma once

#include "ui/tabs/tab.h"
#include "ui/tabs/humidityTab.h"
#include "ui/tabs/temperatureTab.h"
#include "ui/tabs/colorTabs.h"
#include "ui/tabs/fanTab.h"
#include "ui/tabs/emitterTab.h"
#include "ui/tabs/contrastTab.h"
#include "ui/tabs/inversionTab.h"
#include "vector"
#include <cstdint>

class HumidifierApplication;

class Menu {
	public:
		void setup();

		void tick(HumidifierApplication* app);

		uint8_t getSelectedIndex() const;
		void setSelectedIndex(uint8_t value);

		Tab* getSelectedTab();
		void addTab(Tab* tab);

	private:
		std::vector<Tab*> _tabs {};
		uint8_t _selectedIndex = 0;
		bool _oldPressed = false;

		TemperatureTab _temperatureTab = TemperatureTab();
		HumidityTab _humidityTab = HumidityTab();
		HueTab _hueTab = HueTab();
		SaturationTab _saturationTab = SaturationTab();
		BrightnessTab _brightnessTab = BrightnessTab();
		FanTab _fanTab = FanTab();
		EmitterTab _emitterTab = EmitterTab();
		ContrastTab _contrastTab = ContrastTab();
		InversionTab _inversionTab = InversionTab();
};