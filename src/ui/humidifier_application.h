#pragma once

#include <SPI.h>
#include "../hardware/encoder.h"
#include "menu.h"
#include "U8g2lib.h"
#include "../settings.h"

class HumidifierApplication {
	public:
		void setup();

		void tick();

		U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI* getDisplay() {
			return &_display;
		}

		Encoder* getEncoder();

	private:
		Encoder _encoder = Encoder(
			settings::pinout::encoder::clk,
			settings::pinout::encoder::dt,
			settings::pinout::encoder::sw
		);

		Menu _menu = Menu();

		U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI _display = U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI(
			U8G2_R0,
			5,
			17,
			16
		);
};