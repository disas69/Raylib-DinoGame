cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME DinoRun)
project(${PROJECT_NAME})

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.5.0)
    endif()
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

set(RAYLIB_PATH ${PROJECT_SOURCE_DIR}/raylib)
include_directories(${RAYLIB_PATH}/include include)

add_executable(${PROJECT_NAME} src/main.cpp
        src/game/DinoGame.cpp)

if (WIN32)
    link_directories(${RAYLIB_PATH}/lib/win)

    if (MSVC)
        target_link_libraries(${PROJECT_NAME} ${RAYLIB_PATH}/lib/win/raylib.lib)
    else ()
        target_link_libraries(${PROJECT_NAME} ${RAYLIB_PATH}/lib/win/libraylib.a)
    endif ()

    target_link_libraries(${PROJECT_NAME} opengl32 gdi32 winmm)
elseif (APPLE)
    link_directories(${RAYLIB_PATH}/lib/macos)
    target_link_libraries(${PROJECT_NAME} ${RAYLIB_PATH}/lib/macos/libraylib.a)

    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)

    target_link_libraries(${PROJECT_NAME}
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREVIDEO_LIBRARY}
            "-framework OpenGL"
    )
endif ()

target_link_libraries(${PROJECT_NAME} raylib_cpp)