#pragma once

#include "../../lib/YOBA/src/color.h"
#include "../../lib/YOBA/src/resources/fonts/PIXY10Font.h"
#include "../../lib/YOBA/src/resources/fonts/unscii16Font.h"

using namespace yoba;

class Theme {
	public:
		static const MonochromeColor black;
		static const MonochromeColor white;

		static const PIXY10Font fontSmall;
		static const Unscii16Font fontBig;
};