#pragma once

#include "tab.h"

class PowerTab : public Tab {
	public:
		PowerTab();

		void render(Application* app) override;
};