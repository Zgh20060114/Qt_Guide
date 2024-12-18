cmake_minimum_required(VERSION 3.26)
project(003notePad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON) # MOC编译器生成信号与槽的代码
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB source *.cpp)
add_executable(003notePad ${source})
target_link_libraries(003notePad PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

