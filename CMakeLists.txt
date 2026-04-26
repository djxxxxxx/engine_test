cmake_minimum_required(VERSION 3.16)
project(engine_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========== 依赖安装路径 ==========
# 根据平台取消注释，或从命令行传入:
# cmake -DCMAKE_PREFIX_PATH="C:/libs/install" ..
#
# Windows (MinGW/MSVC):
# list(APPEND CMAKE_PREFIX_PATH "C:/libs/install")
#
# Linux:
# list(APPEND CMAKE_PREFIX_PATH "/opt/libs")

# ========== 查找依赖包 ==========
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)
find_package(Jolt REQUIRED)
find_package(OpenGL REQUIRED)

# ========== 源文件 ==========
file(GLOB SOURCES CONFIGURE_DEPENDS
    engine/*.cpp
    game/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# ========== 包含目录 ==========
# 只保留单文件库的头文件 (glad, miniaudio, nuklear)
target_include_directories(${PROJECT_NAME} PRIVATE
    deps/include
)

# ========== 链接库 ==========
target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
    SDL2_image::SDL2_image
    glm::glm
    Jolt::Jolt
    OpenGL::GL
)

# ========== 单文件库源文件 ==========
target_sources(${PROJECT_NAME} PRIVATE
    deps/src/glad.c
)

# ========== Windows 运行时 DLL 拷贝 ==========
if(WIN32)
    # 如果 SDL2 等库是动态链接，自动拷贝 DLL 到输出目录
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
