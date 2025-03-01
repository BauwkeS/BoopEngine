cmake_minimum_required(VERSION 3.26)
project(BoopEngine)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

if(EMSCRIPTEN)
  set(TARGET_NAME BoopEngine_web)
  set(TARGET_PARAM )
else()
  set(TARGET_NAME BoopEngine)
  set(TARGET_PARAM WIN32 )
endif()

# list source files here
add_library(${TARGET_NAME} STATIC
  Boop/HelperFiles/Font.cpp
  Boop/HelperFiles/Font.h
  Boop/HelperFiles/Texture2D.cpp
  Boop/HelperFiles/Texture2D.h
  
  
  Boop/HelperFiles/AnimatedTexture.h
  Boop/HelperFiles/AnimatedTexture.cpp
  
  
  Boop/GameObject.cpp
  Boop/Components/Component.h
  
  Boop/GameObject.h
  Boop/Boop.cpp
  Boop/Boop.h
  Boop/Renderer.cpp
  Boop/Renderer.h
  Boop/ResourceManager.cpp
  Boop/ResourceManager.h
  Boop/Scene/Scene.cpp
  Boop/Scene/Scene.h
  Boop/Scene/SceneManager.cpp
  Boop/Scene/SceneManager.h
  Boop/Scene/LevelLoader.h
  Boop/Scene/LevelLoader.cpp
  Boop/Components/TextureComponent.h
  Boop/Components/TextureComponent.cpp
  Boop/Components/TextComponent.h
  Boop/Components/TextComponent.cpp
  Boop/Components/SpriteComponent.h
  Boop/Components/SpriteComponent.cpp
  Boop/Input/InputManager.cpp
  Boop/Input/InputManager.h
  Boop/Input/Command.h
  
  Boop/Input/Controller.h
  Boop/Input/Controller.cpp
  
  Boop/Event/Observer.h
  
  Boop/Event/Subject.h
  Boop/Event/Subject.cpp
  Boop/States.h

    )

# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

Set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(fmt)

target_link_libraries(${TARGET_NAME} PRIVATE fmt::fmt)

# add SDL2
if (WIN32)
    set(BUILD_SHARED_LIBS OFF)

    message(STATUS "Downloading sdl2...")
    FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-2.30.2
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(sdl2)

    message(STATUS "Downloading sdl2_image...")
    FetchContent_Declare(
        sdl2-image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
        GIT_TAG release-2.8.2
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(sdl2-image)

    # Windows requires building FreeType
    set(SDL2TTF_VENDORED TRUE)

    message(STATUS "Downloading sdl2_ttf...")
    FetchContent_Declare(
        sdl2-ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
        GIT_TAG release-2.22.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(sdl2-ttf)

    set(VLD_DIR "$ENV{ProgramFiles\(x86\)}/Visual Leak Detector")
    if(EXISTS ${VLD_DIR})
        set(VLD_INCLUDE_DIR "${VLD_DIR}/include")
        if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
            set(VLD_LIBRARY "${VLD_DIR}/lib/Win64/vld.lib")
        else()
            set(VLD_LIBRARY "${VLD_DIR}/lib/Win32/vld.lib")
        endif()
    endif()

    target_link_libraries(${TARGET_NAME} PUBLIC XInput)
elseif(NOT EMSCRIPTEN)
    find_package(glm REQUIRED)
    find_package(fmt REQUIRED)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_image REQUIRED)
endif()

if(MSVC)
    target_link_libraries(${TARGET_NAME} PUBLIC SDL2::SDL2main)
endif()

target_link_libraries(${TARGET_NAME} PUBLIC
    glm::glm fmt::fmt
    SDL2::SDL2-static
    SDL2_ttf::SDL2_ttf-static
    SDL2_image::SDL2_image-static
)


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






# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g")
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g -sALLOW_MEMORY_GROWTH --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\" -sSDL2_IMAGE_FORMATS=['tga','png']")

  # work around https://github.com/emscripten-core/emscripten/issues/11513
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -fno-stack-protector")

  # Use the Emscripten toolchain
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/EmscriptenToolchain.cmake)

  # Additional settings for Emscripten build
  set_target_properties(${TARGET_NAME} PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )

  # Have emscripten generate a html page too.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Make sure the asset folder gets copyed or linked correctly
if(WIN32)
    set(SYMLINK_COMMAND copy_directory)
else()
    set(SYMLINK_COMMAND create_symlink)
endif()

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E ${SYMLINK_COMMAND}
                "${CMAKE_SOURCE_DIR}/Data"
                "${CMAKE_BINARY_DIR}/Data")

# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

set_property(TARGET ${TARGET_NAME} PROPERTY
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE
)