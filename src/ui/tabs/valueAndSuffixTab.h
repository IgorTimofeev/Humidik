#pragma once

#include "tab.h"

class ValueAndSuffixTab : public Tab {
	public:
		explicit ValueAndSuffixTab(const wchar_t* name);

		void render(HumidifierApplication* app) override;

	protected:
		wchar_t value[64] {};
		wchar_t suffix[12] {};
};