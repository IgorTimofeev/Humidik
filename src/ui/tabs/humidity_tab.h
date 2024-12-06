#pragma once

#include "value_and_suffix_tab.h"
#include <cstring>
#include <cstdio>
#include <cwchar>

class HumidityTab : public ValueAndSuffixTab {
	public:
		HumidityTab() : ValueAndSuffixTab(L"Humidity") {
			wcscpy(suffix, L"%");
		}

		void tick(HumidifierApplication* app) override {
			uint16_t humidity = 60;

			swprintf(value, sizeof(value), L"%d", humidity);
		}
};