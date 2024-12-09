#pragma once

#include <cstdint>
#include "booleanTab.h"

class ThemeTab : public BooleanTab {
	public:
		explicit ThemeTab();

		void onRotateProcessed() override;

		void setup() override;

		void updateDriver();
};