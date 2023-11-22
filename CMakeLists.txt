cmake_minimum_required(VERSION 3.25)
project(my_Gobang)

set(CMAKE_CXX_STANDARD 17)
#ege图形库导入，我的是F:/My_Clion/mycenv/EGE20.08,此处写自己的ege图形库路径
include_directories(D:/My_Clion/my_lib/EGE20.08/include)
link_directories(D:/My_Clion/my_lib/EGE20.08/lib/mingw64)

add_executable(my_Gobang  main.cpp Calculation.cpp graphicInterface.cpp head.h)

#ege图形库的包
target_link_libraries(my_Gobang libgraphics64.a
        libgdi32.a libimm32.a libmsimg32.a libole32.a
        liboleaut32.a libwinmm.a libuuid.a libgdiplus.a)
