#pragma once

#include <EEPROM.h>

#pragma pack(push, 1)
struct ConfigStrip {
	uint8_t hue = 0x00;
	uint8_t saturation = 0xFF;
	uint8_t brightness = 0xFF;
};

struct ConfigDisplay {
	uint8_t contrast = 0xFF;
	bool invert = true;
};

struct UI {
	uint8_t tabIndex = 0;
	bool focused = false;
};

class Config {
	public:
		UI ui = UI();
		ConfigStrip strip = ConfigStrip();
		ConfigDisplay display = ConfigDisplay();
		uint8_t fanPower = 0xFF;
		uint8_t atomizerPower = 0xFF;
		uint8_t targetHumidity = 60;
		uint16_t shutdownDelay = 0;

		void read() {
			Serial.println("Initializing EEPROM");

			EEPROM.begin(1 + sizeof(Config));

			if (EEPROM.readByte(0) == _previouslySavedFlag) {
				Serial.println("Loading config");

				EEPROM.readBytes(1, this, sizeof(Config));
			}
			else {
				Serial.println("Config wasn't saved, skipping load");
			}
		}

		void write() {
			Serial.println("Saving config");

			EEPROM.writeByte(0, _previouslySavedFlag);
			EEPROM.writeBytes(1, this, sizeof(Config));
			EEPROM.commit();
		}

		void enqueueWrite() {
			_enqueuedWriteDeadline = millis() + 3000;
		}

		void tick() {
			if (_enqueuedWriteDeadline == 0 || millis() < _enqueuedWriteDeadline)
				return;

			_enqueuedWriteDeadline = 0;
			write();
		}

	private:
		static const uint8_t _previouslySavedFlag = 0xAD;

		uint32_t _enqueuedWriteDeadline = 0;
};
#pragma pack(pop)