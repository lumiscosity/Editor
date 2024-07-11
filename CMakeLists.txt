cmake_minimum_required(VERSION 3.16)

project(EasyRPG_Editor VERSION 0.1.0 LANGUAGES CXX)

# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(easyrpg-editor
    src/main.cpp
)

qt_add_qml_module(easyrpg-editor
    URI easyrpg-editor
    QML_FILES
        src/qml/main.qml
    RESOURCES
)

target_link_libraries(easyrpg-editor PRIVATE Qt6::Gui Qt6::Quick)
