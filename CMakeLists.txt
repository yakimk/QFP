cmake_minimum_required(VERSION 3.10)

# Project name
project(QtFunctionPlotter)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Qt5 package
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Set the source and header files
set(SRC_FILES
    src/main.cpp
    src/MainWindow.cpp
    src/PlotWidget.cpp
)

set(HDR_FILES
    src/MainWindow.hpp
    src/PlotWidget.hpp
)

# Include the header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the executable
add_executable(QtFunctionPlotter ${SRC_FILES} ${HDR_FILES})

# Link the Qt5 Widgets library
target_link_libraries(QtFunctionPlotter Qt5::Widgets)

# For automoc and uic (if you have UI files)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include the Qt modules
target_include_directories(QtFunctionPlotter PRIVATE ${Qt5Widgets_INCLUDE_DIRS})
