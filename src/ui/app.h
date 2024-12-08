#pragma once

#include <SPI.h>
#include "../hardware/encoder.h"
#include "../../lib/YOBA/src/hardware/screen/drivers/SH1106Driver.h"
#include "../../lib/YOBA/src/hardware/screen/buffers/monochromeBuffer.h"
#include "../constants.h"
#include "../config.h"
#include "theme.h"
#include "menu.h"

using namespace yoba;

class App {
	public:
		Config config = Config();

		Encoder encoder = Encoder(
			constants::pinout::encoder::clk,
			constants::pinout::encoder::dt,
			constants::pinout::encoder::sw
		);

		Menu menu = Menu();

		SH1106Driver screenDriver = SH1106Driver(
			constants::pinout::screen::chipSelect,
			constants::pinout::screen::dataCommand,
			constants::pinout::screen::reset
		);

		MonochromeBuffer screenBuffer = MonochromeBuffer(&screenDriver);

		static App& getInstance();

		void setup();
		void tick();
};