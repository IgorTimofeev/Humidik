#pragma once

#include <cstdint>
#include "tab.h"

class ProgressTab : public Tab {
	public:
		explicit ProgressTab(const wchar_t* name);

		void render(HumidifierApplication* app) override;

		float getValue() const;
		void setValue(float value);

		void onRotate(HumidifierApplication* app) override;

	private:
		float _value = 0;
};