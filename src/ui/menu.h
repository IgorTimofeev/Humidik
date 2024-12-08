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
//		std::function<Tab*()> govnomassiv[1] {
//			[]() { return new ContrastTab(); }
//		};

		std::vector<Tab*> _tabs {};
		bool _oldPressed = false;
};