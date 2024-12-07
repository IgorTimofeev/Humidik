#pragma once

#include <cstdint>
#include "progressTab.h"

class ColorTab : public ProgressTab {
	public:
		explicit ColorTab(const wchar_t* name);
};

class HueTab : public ColorTab {
	public:
		explicit HueTab();
};

class SaturationTab : public ColorTab {
	public:
		explicit SaturationTab();
};

class BrightnessTab : public ColorTab {
	public:
		explicit BrightnessTab();
};