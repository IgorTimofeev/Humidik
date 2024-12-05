#pragma once

#include "ui/tabs/tab.h"
#include "ui/tabs/sensors_tab.h"
#include "ui/tabs/colors_tab.h"
#include "ui/tabs/power_tab.h"
#include "vector"
#include <cstdint>

class Application;

class Menu {
	public:
		void setup();

		void tick(Application* app);

		int8_t getSelectedIndex() const;
		void setSelectedIndex(int8_t value);

		Tab* getSelectedTab();

		void addTab(Tab* tab) {
			_tabs.push_back(tab);
		}

	private:
		std::vector<Tab*> _tabs {};
		int8_t _selectedIndex = -1;

		SensorsTab _sensorsTab = SensorsTab();
		ColorsTab _colorsTab = ColorsTab();
		PowerTab _powerTab = PowerTab();
};