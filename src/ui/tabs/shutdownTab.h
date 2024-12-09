#pragma once

#include <cwchar>
#include "textAndSuffixTab.h"

class ShutdownTab : public TextAndSuffixTab, public ConfigValueTab<uint16_t> {
	public:
		explicit ShutdownTab();

		void onRotate() override;

		void setup() override;

		void updateTextBuffers();

	private:
		uint32_t _lastRotation = 0;

		wchar_t _textBuffer[4] {};
		wchar_t _suffixBuffer[4] {};
};