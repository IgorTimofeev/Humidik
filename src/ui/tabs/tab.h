#pragma once

class Application;

class Tab {
	public:
		explicit Tab(const char* name);

		void setup();

		virtual void tick(Application* app);

		virtual void render(Application* app) = 0;

		virtual void onRotate() {

		}

		virtual void onPress() {

		}

		const char* getName() const;

	private:
		const char* _name;
};