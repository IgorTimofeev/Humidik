#pragma once

class HumidifierApplication;

class Tab {
	public:
		explicit Tab(const char* name);

		void setup();

		virtual void tick(HumidifierApplication* app);

		virtual void render(HumidifierApplication* app) = 0;

		virtual void onRotate() {

		}

		virtual void onPress() {

		}

		const char* getName() const;

	private:
		const char* _name;
};