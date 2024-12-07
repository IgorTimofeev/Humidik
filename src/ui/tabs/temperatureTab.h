#pragma once

#include "valueAndSuffixTab.h"
#include <cstring>
#include <cstdio>
#include <cwchar>

class TemperatureTab : public ValueAndSuffixTab {
	public:
		TemperatureTab() : ValueAndSuffixTab(L"TEMP") {
			wcscpy(suffix, L"°C");

			setSelectable(false);
		}

		void tick(HumidifierApplication* app) override {
			uint16_t temperature = 24;

			swprintf(value, sizeof(value), L"%d", temperature);
		}
};