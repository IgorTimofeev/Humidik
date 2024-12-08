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
#include <functional>

class App;

class Menu {
	public:
		void setup();

		void tick();

	private:
		std::array<std::function<Tab*()>, 9> _tabs {
			[]() { return new HumidityTab(); },
			[]() { return new TemperatureTab(); },
			[]() { return new HueTab(); },
			[]() { return new SaturationTab(); },
			[]() { return new BrightnessTab(); },
			[]() { return new FanTab(); },
			[]() { return new EmitterTab(); },
			[]() { return new ContrastTab(); },
			[]() { return new InversionTab(); }
		};

		bool _oldPressed = false;
		Tab* _selectedTab = nullptr;
		void switchTab();
};