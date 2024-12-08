#pragma once

#include <cstdint>
#include "progressTab.h"

class EmitterTab : public ProgressTab {
	public:
		explicit EmitterTab();

		void onValueChanged(HumidifierApplication* app) override;
};