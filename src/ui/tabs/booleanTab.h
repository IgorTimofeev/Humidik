#pragma once

#include <cstdint>
#include "tab.h"

class BooleanTab : public Tab, public ConfigValueTab<bool> {
	public:
		explicit BooleanTab(const wchar_t* name, const wchar_t* trueText, const wchar_t* falseText, bool* configValue);

		void render() override;

		void onRotate() override;


	private:
		const wchar_t* _trueText;
		const wchar_t* _falseText;
};