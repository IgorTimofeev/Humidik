#pragma once

#include "ui/tabs/tab.h"
#include "ui/tabs/infoTab.h"
#include "ui/tabs/colorTabs.h"
#include "ui/tabs/fanTab.h"
#include "ui/tabs/atomizerTab.h"
#include "ui/tabs/contrastTab.h"
#include "ui/tabs/themeTab.h"
#include "ui/tabs/shutdownTab.h"
#include "ui/tabs/targetHumidityTab.h"
#include "vector"
#include <cstdint>
#include <functional>

class App;

class Menu {
	public:
		void setup();

		void tick();

	private:
		std::array<Tab*, 10> _tabs {};

		bool _oldPressed = false;
};