cmake_minimum_required(VERSION 3.16)

project(GBJoy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

set(SOURCE_FILES
        "src/main.cpp"
        "src/cpu.cpp"
        "src/ppu.cpp"
        "src/bus.cpp"
        "src/cartridge.cpp"
        "src/screen.cpp"
        "src/joypad.cpp"
        "src/apu.cpp"
        "src/audio.cpp"
)
set(COMPILER_OPTIONS
        "-O3"
        "-Wall"
        "-Wextra"
)

add_executable(GBJoy ${SOURCE_FILES})

target_compile_options(GBJoy PRIVATE ${COMPILER_OPTIONS})
target_include_directories(GBJoy PRIVATE "include")
target_include_directories(GBJoy PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(GBJoy PRIVATE ${SDL2_LIBRARIES})
