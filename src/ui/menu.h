#pragma once

#include "vector"
#include "ui/tabs/tab.h"
#include <cstdint>
#include <functional>

class App;

class Menu {
	public:
		void setup();

		void tick();

	private:
		std::array<Tab*, 10> _tabs {};

		bool _oldPressed = false;
};