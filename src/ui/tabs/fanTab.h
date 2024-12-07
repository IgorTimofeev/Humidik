#pragma once

#include <cstdint>
#include "progressTab.h"

class FanTab : public ProgressTab {
	public:
		explicit FanTab();

		void onRotate(HumidifierApplication* app) override;
};