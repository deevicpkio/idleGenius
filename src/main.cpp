#include "App.hpp"
#include "igcommon.h"

int main () {
    spdlog::set_level(spdlog::level::debug);  // Set specific logger's log level

    App app = App();
    int ret = app.run();
    
    return ret;

}
