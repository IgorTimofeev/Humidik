#pragma once

#include "value_and_suffix_tab.h"
#include <cstring>
#include <cstdio>

class TemperatureTab : public ValueAndSuffixTab {
	public:
		TemperatureTab() : ValueAndSuffixTab("Temperature") {
			strcpy(suffix, "deg");
		}

		void tick(HumidifierApplication* app) override {
			uint16_t temperature = 24;

			snprintf(value, sizeof(value), "%d", temperature);
		}
};