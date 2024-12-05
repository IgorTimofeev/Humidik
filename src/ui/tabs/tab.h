#pragma once

class Application;

class Tab {
	public:
		explicit Tab(const char* name);

		void setup();

		void tick(Application* app);

		void render(Application* app);

		virtual void onRotate() {

		}

		virtual void onPress() {

		}

		const char* getName() const;

	private:
		const char* _name;
};