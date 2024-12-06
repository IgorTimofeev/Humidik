#pragma once

class HumidifierApplication;

class Tab {
	public:
		explicit Tab(const wchar_t* name);

		void setup();

		virtual void tick(HumidifierApplication* app);

		virtual void render(HumidifierApplication* app) = 0;

		virtual void onRotate() {

		}

		virtual void onPress() {

		}

		const wchar_t* getName() const;

	private:
		const wchar_t* _name;
};