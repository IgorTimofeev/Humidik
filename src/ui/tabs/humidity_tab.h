#pragma once

#include "value_and_suffix_tab.h"
#include <cstring>
#include <cstdio>

class HumidityTab : public ValueAndSuffixTab {
	public:
		HumidityTab() : ValueAndSuffixTab("Humidity") {
			strcpy(suffix, "%");
		}

		void tick(Application* app) override {
			uint16_t humidity = 60;

			snprintf(value, sizeof(value), "%d", humidity);
		}
};