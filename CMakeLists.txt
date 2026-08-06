cmake_minimum_required(VERSION 3.20)
project(hangman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain")
endif()

if(DEFINED ENV{VCPKG_ROOT})
    list(PREPEND CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-windows/share")
endif()

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/game/GameState.h
    src/game/WordBank.h
    src/game/HangmanGame.h
    src/game/Difficulty.h
    src/game/ScoreManager.h
    src/ui/Renderer.h
    src/ui/HangmanRenderer.h
    src/ui/KeyboardWidget.h
    src/ui/MenuScreen.h
    src/ui/GameScreen.h
    src/ui/ResultScreen.h
    src/ui/TransitionManager.h
    src/ui/ConfettiRenderer.h
    src/ui/SettingsScreen.h
    src/assets/AssetManager.h
    src/assets/AudioManager.h
    src/utils/StringUtils.h
    src/utils/LocalizationManager.h
    src/utils/SettingsManager.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/data
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env "VCPKG_ROOT=$ENV{VCPKG_ROOT}" powershell -ExecutionPolicy Bypass -File "${CMAKE_CURRENT_SOURCE_DIR}/scripts/copy-deps.ps1" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying runtime DLL dependencies"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
        COMMENT "Copying assets to output directory"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data"
        COMMENT "Copying data to output directory"
    )
endif()
