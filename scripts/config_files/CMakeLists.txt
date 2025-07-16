cmake_minimum_required(VERSION 3.25.0)
set(PROJECT_NAME MetasequoiaImeTsf)
project(${PROJECT_NAME} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(
    /D_UNICODE=1
    /DUNICODE=1
)

include_directories("./")

add_library(${PROJECT_NAME} SHARED
    "./"
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)