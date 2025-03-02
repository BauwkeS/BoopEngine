cmake_minimum_required(VERSION 3.26)
project(BubbleBooble)

add_subdirectory(BoopEngine)

# Add source to this project's executable.
add_executable(${PROJECT_NAME}
"Scr/BubbleBooble.cpp"
"Scr/BubbleBooble.h"
 "Scr/GameLoader.h"
 "Scr/GameLoader.cpp"
 "Scr/Player.cpp"
 "Scr/Player.h"
 "Scr/LevelComponents.h"
 "Scr/LevelComponents.cpp"
 
 
 "Scr/GameCommands.h"
    "TimeEx.cpp" "TimeEx.h"
)


include(FetchContent)
#stolen from: https://github.com/GeleArthur/prog4_engine/blob/671137b4b1fdc27c8a02c10bac4bdd05c00d31a5/CMakeLists.txt

FetchContent_Declare(
        imgui
        URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.8.zip
)
FetchContent_MakeAvailable(imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
)

FetchContent_Declare(
        implot
        URL https://github.com/epezent/implot/archive/refs/tags/v0.16.zip
)
FetchContent_MakeAvailable(implot)
target_include_directories(${PROJECT_NAME} PRIVATE ${implot_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp
        ${implot_SOURCE_DIR}/implot_demo.cpp
)



# Ensure correct target name
if(EMSCRIPTEN)
  set(TARGET_NAME boop_web)
else()
  set(TARGET_NAME boop)
endif()

# Link against the correct target
target_link_libraries(${PROJECT_NAME} PRIVATE BoopEngine)

#use VLD
find_package(VLD CONFIG)
target_include_directories(${PROJECT_NAME} PRIVATE ${VLD_INCLUDE_DIRS})
#target_include_directories(${TARGET_NAME} PRIVATE
  #target_link_libraries( ${PROJECT_NAME} PUBLIC imgui)
  #target_include_directories( ${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE ${VLD_LIBRARIES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# enable c++20 features
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# compile at max warning level + treat warnings as errors
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)