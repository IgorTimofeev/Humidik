#pragma once

#include <cstdint>
#include "tab.h"

class BooleanTab : public Tab {
	public:
		explicit BooleanTab(const wchar_t* name);

		void render() override;

		bool getValue() const;
		void setValue(bool value);

		void onRotate() override;

		virtual void onValueChangedByRotate();
	private:
		bool _value = false;
};