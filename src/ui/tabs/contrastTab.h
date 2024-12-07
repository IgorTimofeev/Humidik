#pragma once

#include <cstdint>
#include "progressTab.h"

class ContrastTab : public ProgressTab {
	public:
		explicit ContrastTab();

		void onRotate(HumidifierApplication* app) override;
};