cmake_minimum_required(VERSION 3.26)
project(BubbleBooble)

add_subdirectory(BoopEngine)

# Add source to this project's executable.
add_executable(${PROJECT_NAME}
"Scr/BubbleBooble.cpp"
"Scr/BubbleBooble.h"
 "Scr/GameLoader.h"
 "Scr/GameLoader.cpp"
 "Scr/Components/Player.cpp"
 "Scr/Components/Player.h"
 
 
 
 
 "Scr/GameCommands.h"
    "Scr/Components/Health.h" "Scr/Components/Health.cpp" "Scr/Components/Events.h" "Scr/Components/HealthObserver.h"
"Scr/Components/HealthObserver.cpp" "Scr/Level.h" "Scr/Level.cpp" "Scr/Components/ScoreObserver.h" "Scr/Components/ScoreObserver.cpp" "Scr/Components/BaseTank.cpp" "Scr/Components/BaseTank.h" "Scr/Components/Enemy.h" "Scr/Components/Enemy.cpp")

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

# Make sure the asset folder gets copyed or linked correctly
if(WIN32)
    set(SYMLINK_COMMAND copy_directory)
else()
    set(SYMLINK_COMMAND create_symlink)
endif()

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E ${SYMLINK_COMMAND}
                "${CMAKE_SOURCE_DIR}/Data"
                "${CMAKE_BINARY_DIR}/Data")

# enable c++20 features
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# compile at max warning level + treat warnings as errors
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)