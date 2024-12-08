#pragma once

#include <cstdint>

class App;

class Tab {
	public:
		explicit Tab(const wchar_t* name);

		virtual ~Tab() = default;

		virtual void setup();
		virtual void tick();
		virtual void onRotate();
		virtual void render() = 0;

		const wchar_t* getName() const;
		bool isFocusable() const;
		void setFocusable(bool selectable);

	private:
		const wchar_t* _name;
		bool _focusable = true;
};