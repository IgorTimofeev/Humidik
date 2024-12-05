#pragma once

#include "tab.h"

class ColorsTab : public Tab {
	public:
		ColorsTab();

		void render(Application* app) override;
};