#pragma once

#include <cstdint>
#include "progressTab.h"

class EmitterTab : public ProgressTab {
	public:
		explicit EmitterTab();

		void onRotate(HumidifierApplication* app) override;
};