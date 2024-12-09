#pragma once

#include <cwchar>
#include "textAndSuffixTab.h"

class TargetHumidityTab : public TextAndSuffixTab, public ConfigValueTab<uint8_t> {
	public:
		explicit TargetHumidityTab();

		void onRotate() override;

		void setup() override;

		void updateTextBuffers();

	private:
		uint32_t _lastRotation = 0;

		wchar_t _textBuffer[4] {};
		wchar_t _suffixBuffer[2] {};
};