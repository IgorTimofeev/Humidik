#pragma once

#include <cstdint>
#include "progressTab.h"

class ContrastTab : public ProgressTab {
	public:
		explicit ContrastTab();

		void onRotateProcessed() override;
		void setup() override;

		void updateContrast();
};