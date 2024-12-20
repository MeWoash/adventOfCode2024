cmake_minimum_required(VERSION 3.10)
project(template)

set(CMAKE_CXX_STANDARD 23)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        )
endif()

# ========= SOURCE FILES =============
file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp"
                    "${PROJECT_SOURCE_DIR}/../utils/src/*.cpp")
# set(SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/secondFile.cpp)
add_executable(out ${SRC_FILES})

# ========= HEADER FILES =============
set(HEADER_DIRS "${PROJECT_SOURCE_DIR}/include"
                "${PROJECT_SOURCE_DIR}/../utils/include")
target_include_directories(out PUBLIC ${HEADER_DIRS})


# DEBUG PRINTS
message("Detected header dirs:")
foreach(HEADER_DIR ${HEADER_DIRS})
    message(" - ${HEADER_DIR}")
endforeach()

message("Detected source files:")
foreach(SRC_FILE ${SRC_FILES})
    message(" - ${SRC_FILE}")
endforeach()