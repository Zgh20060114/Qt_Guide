cmake_minimum_required(VERSION 3.26)
project(qt_guide)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON) # 自动处理 Qt 的信号和槽机制
set(CMAKE_AUTORCC ON) # 自动启用RCC（Qt资源编译器）处理qrc文件
set(CMAKE_AUTOUIC ON) # 自动启用UIC（Qt界面编译器）处理ui文件

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
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB source *.cpp)
add_executable(qt_guide ${source})

target_link_libraries(qt_guide PRIVATE #底下这些库在qt_guide被链接到其他target时不会被自动链接
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

