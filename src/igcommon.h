#ifndef IG_COMMON
#define IG_COMMON
#include <sstream>
#include <spdlog/spdlog.h>

#define SCREEN_WIDTH_DEFAULT 1920
#define SCREEN_HEIGHT_DEFAULT 1200

enum ERROR_HANDLING {
		SUCCESS = 0,
		FAILED_INIT,
		FAILED_LOOP,
};

template <typename T>
std::string to_string_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}
#endif
