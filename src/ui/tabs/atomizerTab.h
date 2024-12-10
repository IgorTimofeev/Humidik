#pragma once

#include <cstdint>
#include "progressTab.h"

class AtomizerTab : public ProgressTab {
	public:
		explicit AtomizerTab();

		void onRotateProcessed() override;
};