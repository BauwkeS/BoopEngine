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
 "Scr/States.h"
 "Scr/States.cpp"
 "Scr/GameCommands.h"
 "Scr/GameCommands.cpp"  )

# Ensure correct target name
if(EMSCRIPTEN)
  set(TARGET_NAME boop_web)
else()
  set(TARGET_NAME boop)
endif()

# Link against the correct target
target_link_libraries(${PROJECT_NAME} PRIVATE BoopEngine)

find_package(VLD CONFIG)
target_include_directories(${PROJECT_NAME} PRIVATE ${VLD_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${VLD_LIBRARIES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# enable c++20 features
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# compile at max warning level + treat warnings as errors
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)