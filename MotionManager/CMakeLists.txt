cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED)

file(GLOB WalkingManager_SRC
        "*.h"
        "*.cpp"
        )

add_executable(WalkingManager ${WalkingManager_SRC})

target_link_libraries(WalkingManager ${OpenCV_LIBS})