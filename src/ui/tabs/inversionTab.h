#pragma once

#include <cstdint>
#include "booleanTab.h"

class InversionTab : public BooleanTab {
	public:
		explicit InversionTab();

		void onValueChanged(HumidifierApplication* app) override;
};