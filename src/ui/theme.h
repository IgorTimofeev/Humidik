#pragma once

#include "../../lib/YOBA/src/color.h"
#include "../../lib/YOBA/src/resources/fonts/PIXY10Font.h"
#include "../../lib/YOBA/src/resources/fonts/unscii16Font.h"
#include "../resources/fonts/Arial26Font.h"
#include "../resources/fonts/Arial20Font.h"

using namespace yoba;

class Theme {
	public:
		static const MonochromeColor white;
		static const MonochromeColor black;

		static const PIXY10Font fontSmall;
		static const Arial20Font fontMedium;
		static const Arial26Font fontBig;
};