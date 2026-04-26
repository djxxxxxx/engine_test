cmake_minimum_required(VERSION 3.16)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${CMAKE_SOURCE_DIR}/deps/include")
link_directories("${CMAKE_SOURCE_DIR}/deps/lib")

file(GLOB SOURCES CONFIGURE_DEPENDS engine/*.cpp game/*.cpp deps/src/*.c)
add_executable(app ${SOURCES})

target_link_libraries(app
    libSDL2.dll.a
    libSDL2_image.dll.a
    libglm.a
    libJolt.a
    opengl32
)

# 编译完成后，将 deps/bin 下的所有文件（如 DLL）拷贝到可执行文件所在目录
if(EXISTS "${CMAKE_SOURCE_DIR}/deps/bin")
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/deps/bin"
        $<TARGET_FILE_DIR:app>
    )
endif()

# 将 shader 目录拷贝到可执行文件所在目录
if(EXISTS "${CMAKE_SOURCE_DIR}/shader")
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shader"
        "$<TARGET_FILE_DIR:app>/shader"
    )
endif()

# 获取 build/ 根目录（假设 CMAKE_BINARY_DIR 为 build/debug 或 build/release）
get_filename_component(BUILD_ROOT_DIR "${CMAKE_BINARY_DIR}" DIRECTORY)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${BUILD_ROOT_DIR}/compile_commands.json"
    COMMENT "Copying compile_commands.json to build root"
)

# test