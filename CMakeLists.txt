cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(raylib_app.out VERSION 1.0 DESCRIPTION "Idle Genius")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib 4.5 REQUIRED) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Find SQlite3 API library
find_package(SQLite3 REQUIRED)

# Find SPDlog API library
find_package(spdlog REQUIRED)

# Project
add_executable(${PROJECT_NAME} 
		src/main.cpp
		src/App.cpp
		src/Scene.cpp
		src/dbModels/DBManager.cpp
		src/dbModels/ProfileModel.cpp
		src/dbModels/GeneratorModel.cpp
)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
# Link SQlite3 library
target_link_libraries(${PROJECT_NAME} SQLite::SQLite3 )
# Link SDPLog library (header only)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog_header_only)

