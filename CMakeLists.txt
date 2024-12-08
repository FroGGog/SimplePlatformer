cmake_minimum_required(VERSION 3.16)

project(Assigment3 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraires" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

set(SFML_BUILD_NETWORK FALSE) 
FetchContent_MakeAvailable(SFML)

# add imgui to project
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
)

FetchContent_MakeAvailable(imgui)

# add imgui+sfml to project
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35
)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)

set(SOURCE_FILES

    "src/main.cpp"
    
    "src/Components.h"

    "src/Entity.h"
    "src/Entity.cpp"

    "src/EntityManager.h"
    "src/EntityManager.cpp"

    "src/GameEngine.h"
    "src/GameEngine.cpp"

    "src/Scene.h"
    "src/Scene.cpp"

    "src/LevelScene.h"
    "src/LevelScene.cpp"

    "src/MainMenuScene.h"
    "src/MainMenuScene.cpp"

    "src/Action.h"
    "src/Action.cpp"

    "src/Assets.h"
    "src/Assets.cpp"

    "src/Physics.h"
    "src/Physics.cpp"

    "src/Animation.h"
    "src/Animation.cpp"

)


add_executable(Assigment3 ${SOURCE_FILES})
target_link_libraries(Assigment3 PRIVATE sfml-graphics)
target_link_libraries(Assigment3 PRIVATE ImGui-SFML::ImGui-SFML)
target_compile_features(Assigment3 PRIVATE cxx_std_17)


# Dirs to font
set(FONT_FILES

    "${CMAKE_SOURCE_DIR}/src/assets/grid.ttf"
    "${CMAKE_SOURCE_DIR}/src/assets/menu.ttf"

)

# Copy font file to build dir
add_custom_command(TARGET Assigment3
    # create directory in build dir
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Assigment3>/fonts
    COMMAND ${CMAKE_COMMAND} -E copy ${FONT_FILES} $<TARGET_FILE_DIR:Assigment3>/fonts
    COMMENT "Copying font files to output directory"
)


# Copy texture file to output directory
set(TEXTURES

    "${CMAKE_SOURCE_DIR}/src/assets/textures/Brick.png"
    "${CMAKE_SOURCE_DIR}/src/assets/textures/Bush1.png"
    "${CMAKE_SOURCE_DIR}/src/assets/textures/Bush2.png"
    "${CMAKE_SOURCE_DIR}/src/assets/textures/PipeBL.png"
    "${CMAKE_SOURCE_DIR}/src/assets/textures/PipeBR.png"
    "${CMAKE_SOURCE_DIR}/src/assets/textures/PipeUL.png"
    "${CMAKE_SOURCE_DIR}/src/assets/textures/PipeUR.png"

    "${CMAKE_SOURCE_DIR}/src/assets/textures/MarioIDLE.png"
    "${CMAKE_SOURCE_DIR}/src/assets/animations/MarioRun.png"

)

add_custom_command(TARGET Assigment3 
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Assigment3>/textures
    COMMAND ${CMAKE_COMMAND} -E copy ${TEXTURES} $<TARGET_FILE_DIR:Assigment3>/textures
    COMMENT "Copying texture file to output directory"
)

# Config files
set(CONFIGS

    "${CMAKE_SOURCE_DIR}/src/AssetsLoad.txt"

)

add_custom_command(TARGET Assigment3 
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Assigment3>/configs
    COMMAND ${CMAKE_COMMAND} -E copy ${CONFIGS} $<TARGET_FILE_DIR:Assigment3>/configs
    COMMENT "Copying config files to output directory"
)


if(WIN32)
    add_custom_command(
        TARGET Assigment3
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Assigment3>
        VERBATIM)
endif()