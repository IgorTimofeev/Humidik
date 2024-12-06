#pragma once

#include "tab.h"

class ValueAndSuffixTab : public Tab {
	public:
		explicit ValueAndSuffixTab(const char* name);

		void render(HumidifierApplication* app) override;

	protected:
		char value[64] {};
		char suffix[12] {};
};