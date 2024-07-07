#include "App.hpp"
#include <sqlite3.h>
#include <spdlog/spdlog.h>

int main () {
    spdlog::set_level(spdlog::level::debug);  // Set specific logger's log level

    App app = App();
    int ret = app.Run();
    
    return ret;

}
