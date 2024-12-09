#pragma once

#include <cstdint>
#include "tab.h"

class ProgressTab : public Tab, public ValueTab<float>, public ConfigValueTab<uint8_t> {
	public:
		explicit ProgressTab(const wchar_t* name, uint8_t* configValue);

		void setup() override;

		void render() override;

		void onRotate() override;

	private:
		uint32_t _lastRotation = 0;
};

// -------------------------------- PWMProgressTab --------------------------------

class PWMProgressTab : public ProgressTab {
	public:
		explicit PWMProgressTab(const wchar_t* name, uint8_t pin, uint8_t* configValue);

		void setup() override;
		void onRotateProcessed() override;

	private:
		uint8_t _pin;

		void pwm();
};