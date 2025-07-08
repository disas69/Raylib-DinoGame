cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Dino)
project(${PROJECT_NAME})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

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

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/misc/easing.cpp
        src/game/Game.cpp
        src/game/AssetManager.cpp
        src/game/Player.cpp
        src/game/UIManager.cpp
        src/game/Obstacle.cpp
)

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
elseif (UNIX AND NOT APPLE)
    link_directories(${RAYLIB_PATH}/lib/linux)
    target_link_libraries(${PROJECT_NAME} ${RAYLIB_PATH}/lib/linux/libraylib.a)

    find_package(OpenGL REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)

    target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}
            ${OPENGL_gl_LIBRARY}
            ${GLFW_LIBRARIES}
            pthread
            m
            dl
            X11
    )
endif ()

target_link_libraries(${PROJECT_NAME} raylib_cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)