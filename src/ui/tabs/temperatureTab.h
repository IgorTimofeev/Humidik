#pragma once

#include "valueAndSuffixTab.h"
#include <cstring>
#include <cstdio>
#include <cwchar>

class TemperatureTab : public ValueAndSuffixTab {
	public:
		TemperatureTab() : ValueAndSuffixTab(L"TEMP") {
			wcscpy(suffix, L"°C");

			setFocusable(false);
		}

		void tick() override {
			uint16_t temperature = 24;

			swprintf(value, sizeof(value), L"%d", temperature);
		}
};