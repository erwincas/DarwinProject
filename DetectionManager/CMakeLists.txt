cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED)
find_package (Threads)

file(GLOB DetectionManager_SRC
        "*.h"
        "*.cpp"
        )

add_executable(DetectionManager ${DetectionManager_SRC})

target_link_libraries (DetectionManager ${CMAKE_THREAD_LIBS_INIT} rt ${OpenCV_LIBS})
set_property(TARGET DetectionManager PROPERTY CXX_STANDARD 11)

