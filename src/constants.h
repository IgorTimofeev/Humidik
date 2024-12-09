#pragma once

#include "cstdint"

namespace constants {
	namespace pinout {
		namespace encoder {
			const uint8_t clk = 22;
			const uint8_t dt = 4;
			const uint8_t sw = 21;
		}

		namespace screen {
			const uint8_t chipSelect = 5;
			const uint8_t dataCommand = 17;
			const uint8_t reset = 16;
		}

		const uint8_t fan = 19;
		const uint8_t atomizer = 33;
	}
}