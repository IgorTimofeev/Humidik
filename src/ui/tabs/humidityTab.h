#pragma once

#include "valueAndSuffixTab.h"
#include <cstring>
#include <cstdio>
#include <cwchar>

class HumidityTab : public ValueAndSuffixTab {
	public:
		HumidityTab() : ValueAndSuffixTab(L"HMDT") {
			wcscpy(suffix, L"%");

			setFocusable(false);
		}

		void tick() override {
			uint16_t humidity = 60;

			swprintf(value, sizeof(value), L"%d", humidity);
		}
};