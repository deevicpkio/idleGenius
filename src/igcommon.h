#ifndef IG_COMMON
#define IG_COMMON
#include <spdlog/spdlog.h>

#define SCREEN_WIDTH_DEFAULT 1920
#define SCREEN_HEIGHT_DEFAULT 1200

enum ERROR_HANDLING {
		SUCCESS = 0,
		FAILED_INIT,
		FAILED_LOOP,
};

#endif
