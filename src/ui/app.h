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

		SH1106Driver screenDriver = SH1106Driver(
			constants::pinout::screen::chipSelect,
			constants::pinout::screen::dataCommand,
			constants::pinout::screen::reset
		);

		MonochromeBuffer screenBuffer = MonochromeBuffer(&screenDriver);

		Menu menu = Menu();

		static App& getInstance();

		void setup();
		void tick();
		float getTemperature() const;
		float getHumidity() const;

		void updateFanPower();
		void updateAtomizerPower();
		void updateFanAndAtomizerPower();

		uint32_t getShutdownTime() const;
		void updateShutdownTimeConditional();

	private:
		float _temperature = 0;
		float _humidity = 0;
		uint32_t _sensorsTickDeadline = 0;

		uint32_t _shutdownTime = 0;
		bool _shutdownState = false;

		void readSensors();

		void analogWriteToDevice(uint8_t pin, uint8_t value) const;

		void updateShutdownTime();
};