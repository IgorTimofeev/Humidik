#pragma once

#include "DHTesp.h"
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
		static const uint8_t marginTop = 5;

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

		DHTesp atmosphericSensor = DHTesp();

		static App& getInstance();

		void setup();
		void tick();
		float getTemperature() const;
		float getHumidity() const;

		void updateFanPower();
		void updateAtomizerPower();

		uint32_t getShutdownTime() const;
		void updateShutdownTimeIfTimerEnabled();

		bool isAtmosphericDataAvailable() const;

	private:
		float _temperature = NAN;
		float _humidity = NAN;
		bool _targetHumidityReached = false;
		uint32_t _atmosphericSensorTickTime = 0;
		uint32_t _shutdownTime = 0;

		void setFanOrAtomizerPower(uint8_t pin, uint8_t value) const ;
		void readAtmosphericSensor();
		void updateShutdownTime();
		void checkTargetHumidity();
		void checkShutdownTime();
		void updateFanAndAtomizerPower();
};