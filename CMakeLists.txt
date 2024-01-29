cmake_minimum_required(VERSION 3.27)
project(minecraft)

set(CMAKE_CXX_STANDARD 17)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copying assets directory to build directory"
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(MINECRAFT_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(MINECRAFT_RELEASE)
endif ()

find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")

        execute_process(
                COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT
        )

        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif ()
    endif ()
endif ()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif ()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/spdlog/CMakeLists.txt")
    message(FATAL_ERROR "The spdlog submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif ()

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/spdlog)

set(IMGUI_DIR thirdparty/imgui)

include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

file(GLOB_RECURSE SOURCES
        src/*.cpp
        src/*.h
        include/*.cpp
        include/*.h
)

# Include GLAD
set(SOURCES ${SOURCES}
        thirdparty/include/glad/glad.c
        thirdparty/include/fastnoiselite/fastnoiselite.h
)

set(IMGUI_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        include
        thirdparty/include
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw spdlog)

# Copy dlls to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:spdlog>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying DLLs to build directory"
)
