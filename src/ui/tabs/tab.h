#pragma once

#include <cstdint>

class HumidifierApplication;

class Tab {
	public:
		explicit Tab(const wchar_t* name);

		void setup();

		virtual void tick(HumidifierApplication* app);

		virtual void render(HumidifierApplication* app) = 0;

		virtual void onRotate(HumidifierApplication* app);

		const wchar_t* getName() const;

		bool isSelected() const;
		void setSelected(bool value);

		bool isSelectable() const;

		void setSelectable(bool selectable);

	private:
		const wchar_t* _name;
		bool _active = false;
		bool _selected = true;
		bool _selectable = true;
};