#pragma once

#include "tab.h"

class TextAndSuffixTab : public Tab {
	public:
		explicit TextAndSuffixTab(const wchar_t* name);

		void render() override;

		wchar_t* getText() const;
		void setText(wchar_t* text);

		wchar_t* getSuffix() const;
		void setSuffix(wchar_t* suffix);

	private:
		wchar_t* _text = nullptr;
		wchar_t* _suffix = nullptr;
};