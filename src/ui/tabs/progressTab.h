#pragma once

#include <cstdint>
#include "tab.h"

class ProgressTab : public Tab {
	public:
		explicit ProgressTab(const wchar_t* name);

		void render() override;

		float getValue() const;
		void setValue(float value);

		void onRotate() override;

		virtual void onValueChanged();

	private:
		float _value = 0;
		uint32_t _lastRotation = 0;
};

class PWMProgressTab : public ProgressTab {
	public:
		explicit PWMProgressTab(const wchar_t* name, uint8_t pin, uint8_t* configValue);

		void setup() override;

		void onValueChanged() override;

	private:
		uint8_t* _configValue;
		uint8_t _pin;

		void pwm() const;
};