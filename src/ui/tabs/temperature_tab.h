#pragma once

#include "value_and_suffix_tab.h"
#include <cstring>
#include <cstdio>
#include <cwchar>

class TemperatureTab : public ValueAndSuffixTab {
	public:
		TemperatureTab() : ValueAndSuffixTab(L"Temperature") {
			wcscpy(suffix, L"°C");
		}

		void tick(HumidifierApplication* app) override {
			uint16_t temperature = 24;

			swprintf(value, sizeof(value), L"%d", temperature);
		}
};