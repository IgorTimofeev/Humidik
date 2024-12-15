#pragma once

#include <cstdint>
#include "../../../lib/YOBA/src/font.h"

using namespace yoba;

class App;

// -------------------------------- Tab --------------------------------

class Tab {
	public:
		explicit Tab(const wchar_t* name);

		virtual ~Tab() = default;

		virtual void setup();
		virtual void render() = 0;
		virtual void onRotate();
		virtual void onRotateProcessed();
		const wchar_t* getName() const;
		bool isFocusable() const;
		void setFocusable(bool selectable);

	protected:
		static void renderCenteredText(const Font* font, const wchar_t* text);

	private:
		const wchar_t* _name;
		bool _focusable = true;
};

// -------------------------------- ValueTab --------------------------------

template<typename TValue>
class ValueTab {
	public:
		TValue getValue() const;

		void setValue(TValue value);

	private:
		TValue _value;
};

template<typename TValue>
TValue ValueTab<TValue>::getValue() const {
	return _value;
}

template<typename TValue>
void ValueTab<TValue>::setValue(TValue value) {
	_value = value;
}

// -------------------------------- ConfigValueTab --------------------------------

template<typename TValue>
class ConfigValueTab {
	public:
		explicit ConfigValueTab(TValue* configValue);

		TValue* getConfigValue();

	private:
		TValue* _configValue;
};

template<typename TValue>
ConfigValueTab<TValue>::ConfigValueTab(TValue* configValue) : _configValue(configValue) {

}

template<typename TValue>
TValue* ConfigValueTab<TValue>::getConfigValue() {
	return _configValue;
}