cmake_minimum_required(VERSION 3.5)

project(history_test_class_serverfunctions LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(history_test_class_serverfunctions tst_history_test_class_serverfunctions.cpp)
add_test(NAME history_test_class_serverfunctions COMMAND history_test_class_serverfunctions)

target_link_libraries(history_test_class_serverfunctions PRIVATE Qt${QT_VERSION_MAJOR}::Test)

