#pragma once

#include <cstdint>
#include "tab.h"

class BooleanTab : public Tab {
	public:
		explicit BooleanTab(const wchar_t* name);

		void render(HumidifierApplication* app) override;

		bool getValue() const;
		void setValue(bool value);

		void onRotate(HumidifierApplication* app) override;

		virtual void onValueChanged(HumidifierApplication* app) {

		}
	private:
		bool _value = false;
};