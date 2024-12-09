#pragma once

#include "tab.h"
#include <cstring>
#include <cstdio>
#include <cwchar>

class InfoTab : public Tab {
	public:
		InfoTab();
		void tick() override;
		void render() override;

	private:
		wchar_t _humidityTextBuffer[6] {};
		wchar_t _humiditySuffixBuffer[2] {};

		wchar_t _temperatureTextBuffer[6] {};
		wchar_t _temperatureSuffixBuffer[3] {};
};