#pragma once

#include <QString>

#include "wke.h"
#include "Logger.hpp"

class callJsFunc {
public:
	static void jumpTo(wkeWebView& webView, const QPair<float, float> position) {
		auto code = QString("jumpTo(%1, %2);")
			.arg(position.first)
			.arg(position.second);
		DEBUG(code);

		wkeRunJS(webView, code.toUtf8());
	}
};

