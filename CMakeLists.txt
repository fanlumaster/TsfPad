cmake_minimum_required(VERSION 3.25.0)
set(PROJECT_NAME TsfPad)
project(${PROJECT_NAME} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(
    /D_UNICODE=1
    /DUNICODE=1
)

# fmt
find_package(fmt CONFIG REQUIRED)

include_directories("./")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MY_EXECUTABLE_NAME "TsfPad")

add_executable(${PROJECT_NAME} WIN32
    "./DisplayAttribute.cpp"
    "./DisplayAttribute.h"
    "./private.h"
    "./resource.h"
    "./TextContainer.cpp"
    "./TextContainer.h"
    "./TextEditor.cpp"
    "./TextEditor.h"
    "./TextEditSink.cpp"
    "./TextEditSink.h"
    "./TextInputCtrl.cpp"
    "./TextInputCtrl.h"
    "./TextLayout.cpp"
    "./TextLayout.h"
    "./TextStore.cpp"
    "./TextStore.h"
    "./TsfPad.cpp"
    "./TsfPad.h"
    "./TsfPad.rc"
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    imm32.lib
    fmt::fmt-header-only
)