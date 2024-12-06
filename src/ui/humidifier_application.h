#pragma once

#include <SPI.h>
#include "../hardware/encoder.h"
#include "../../lib/YOBA/src/hardware/screen/drivers/SH1106Driver.h"
#include "../../lib/YOBA/src/hardware/screen/buffers/monochromeBuffer.h"
#include "../settings.h"
#include "theme.h"
#include "menu.h"

using namespace yoba;

class HumidifierApplication {
	public:
		void setup();

		void tick();

		MonochromeBuffer* getDisplay();

		Encoder* getEncoder();

	private:
		Encoder _encoder = Encoder(
			settings::pinout::encoder::clk,
			settings::pinout::encoder::dt,
			settings::pinout::encoder::sw
		);

		Menu _menu = Menu();

		SH1106Driver screenDriver = SH1106Driver(
			settings::pinout::screen::chipSelect,
			settings::pinout::screen::dataCommand,
			settings::pinout::screen::reset
		);

		MonochromeBuffer _display = MonochromeBuffer(&screenDriver);
};