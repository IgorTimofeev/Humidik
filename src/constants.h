#pragma once

#include "cstdint"

namespace constants {
	namespace pinout {
		namespace encoder {
			const uint8_t clk = 22;
			const uint8_t dt = 21;
			const uint8_t sw = 4;
		}

		namespace screen {
			const uint8_t chipSelect = 5;
			const uint8_t dataCommand = 17;
			const uint8_t reset = 16;
		}

		const uint8_t fan = 19;
		const uint8_t atomizer = 33;
		const uint8_t atmosphericSensor = 15;
	}

	const uint8_t targetHumidityThreshold = 5;
}