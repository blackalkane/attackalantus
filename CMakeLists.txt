cmake_minimum_required(VERSION 3.1)
project(attackAtlantis)

# Set c++11
# https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
if (POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif ()
set(CMAKE_CXX_STANDARD 11)

# nice hierarchichal structure in MSVC
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Find OS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(IS_OS_MAC 1)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(IS_OS_LINUX 1)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(IS_OS_WINDOWS 1)
else ()
    message(FATAL_ERROR "OS ${CMAKE_SYSTEM_NAME} was not recognized")
endif ()

# Create executable target

# Generate the shader folder location to the header
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/project_path.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/project_path.hpp")

# You can switch to use the file GLOB for simplicity but at your own risk
# file(GLOB SOURCE_FILES src/*.cpp src/*.hpp)

set(SOURCE_FILES
        src/project_path.hpp
        src/main.cpp
        src/levels.hpp
        src/levels.cpp
        src/common.hpp
        src/world.hpp
        src/global.hpp
        src/common.cpp
        src/world.cpp
        src/mainMenu.hpp
        src/mainMenu.cpp
        src/levelSelection.hpp
        src/levelSelection.cpp
        src/winLose.hpp
        src/winLose.cpp
        src/tutorialLevel.hpp
        src/tutorialLevel.cpp
        src/gameState.cpp src/gameState.hpp
        src/levelName.hpp
        src/decisionTree.cpp src/decisionTree.hpp
        src/allSystem.cpp
        src/allSystem.hpp
        src/leaderboard.cpp src/leaderboard.hpp

        src/systems/system.hpp
        src/systems/collisionSystem.hpp
        src/systems/collisionSystem.cpp
        src/systems/drawSystem.hpp
        src/systems/drawSystem.cpp
        src/systems/moveSystem.hpp
        src/systems/moveSystem.cpp
        src/systems/simpleAISystem.hpp
        src/systems/simpleAISystem.cpp
        src/systems/shootingAISystem.cpp
        src/systems/shootingAISystem.hpp
        src/systems/bossAISystem.cpp
        src/systems/bossAISystem.hpp
        src/systems/musicSystem.cpp
        src/systems/musicSystem.hpp
        src/systems/scoreSystem.cpp
        src/systems/scoreSystem.hpp
        src/systems/soundSystem.cpp
        src/systems/soundSystem.hpp
        src/systems/controlSystem.cpp
        src/systems/abilitySystem.cpp
        src/systems/abilitySystem.hpp
        src/systems/spawnLimits.hpp
        src/systems/spawnSystem.cpp
        src/systems/spawnSystem.hpp
        src/systems/deleteSystem.cpp
        src/systems/deleteSystem.hpp
        src/systems/missileSystem.cpp
        src/systems/missileSystem.hpp

        src/components/componentType.hpp
        src/components/gcomponent.hpp
        src/components/dropBomb.hpp
        src/components/dropBomb.cpp
        src/components/explosion.hpp
        src/components/explosion.cpp
        src/components/drawComponent.hpp
        src/components/drawComponent.cpp
        src/components/positionComponent.hpp
        src/components/positionComponent.cpp
        src/components/velocityComponent.hpp
        src/components/velocityComponent.cpp
        src/components/healthComponent.hpp
        src/components/healthComponent.cpp
        src/components/basicSlash.cpp
        src/components/basicSlash.hpp
        src/components/abilityComponent.hpp
        src/components/blinkSlash.cpp
        src/components/blinkSlash.hpp
        src/components/shoot.cpp
        src/components/shoot.hpp
        src/components/boomerangAbility.cpp
        src/components/boomerangAbility.hpp
        src/components/onFire.cpp
        src/components/onFire.hpp

        src/entities/entity.hpp
        src/entities/entityType.hpp
        src/entities/drawable.hpp
        src/entities/movable.hpp
        src/entities/theguy.hpp
        src/entities/theguy.cpp
        src/entities/bomb.hpp
        src/entities/bomb.cpp
        src/entities/slash.hpp
        src/entities/slash.cpp
        src/entities/gun.hpp
        src/entities/gun.cpp
        src/entities/bombExplosion.hpp
        src/entities/bombExplosion.cpp
        src/entities/enemy.hpp
        src/entities/basicEnemy.hpp
        src/entities/basicEnemy.cpp
        src/entities/shootingEnemy.hpp
        src/entities/shootingEnemy.cpp
        src/entities/speedEnemy.hpp
        src/entities/speedEnemy.cpp
        src/entities/bossEnemy.cpp
        src/entities/bossEnemy.hpp
        src/entities/projectile.hpp
        src/entities/projectile.cpp
        src/entities/enemyProjectile.cpp
        src/entities/enemyProjectile.hpp
        src/entities/rock.hpp
        src/entities/rock.cpp
        src/entities/waterCurrent.hpp
        src/entities/waterCurrent.cpp
        src/entities/environment.cpp
        src/entities/environment.hpp
        src/entities/bossEnemy2.cpp
        src/entities/bossEnemy2.hpp
        src/entities/hasAbility.hpp
        src/entities/enemyType.hpp
        src/entities/abilityContainer.cpp
        src/entities/abilityContainer.hpp
        src/entities/hasHealth.hpp
        src/entities/healthBar.cpp
        src/entities/healthBar.hpp
        src/entities/menu.cpp
        src/entities/menu.hpp
        src/entities/menu_items.cpp
        src/entities/menu_items.hpp
        src/entities/levelSelectionBackground.cpp
        src/entities/levelSelectionBackground.hpp
        src/entities/defaultTexture.cpp
        src/entities/defaultTexture.hpp
        src/entities/castle.cpp
        src/entities/castle.hpp
        src/entities/castleTop.cpp
        src/entities/castleTop.hpp
        src/entities/enemyProjectile.cpp
        src/entities/enemyProjectile.hpp
        src/entities/boomerangProjectile.cpp
        src/entities/boomerangProjectile.hpp
        src/entities/boomerangIcon.cpp
        src/entities/boomerangIcon.hpp
        src/entities/projectileType.hpp
        src/entities/glyph.cpp
        src/entities/glyph.hpp
        src/systems/particleEffectSystem.cpp
        src/systems/particleEffectSystem.hpp
        src/entities/projectileType.hpp
        src/entities/particle.cpp
        src/entities/particle.hpp
        src/systems/dynamicEntityStoreSystem.cpp
        src/systems/dynamicEntityStoreSystem.hpp
        src/entities/rainDrop.cpp
        src/entities/rainDrop.hpp
        src/entities/pork.cpp
        src/entities/pork.hpp
        src/entities/meteoroid.cpp
        src/entities/meteoroid.hpp
        src/entities/meteoroidIcon.cpp
        src/entities/meteoroidIcon.hpp
        src/components/meteoroidAbility.cpp
        src/components/meteoroidAbility.hpp
        src/entities/fireLittleParticle.cpp
        src/entities/fireLittleParticle.hpp
        src/entities/firePet.cpp
        src/entities/firePet.hpp
        src/systems/petRouteSystem.cpp
        src/systems/petRouteSystem.hpp
        src/systems/particleEffectSystem.cpp
        src/systems/particleEffectSystem.hpp
        src/systems/bossAISystem2.cpp
        src/systems/bossAISystem2.hpp
        src/entities/bossProjectile.cpp
        src/entities/bossProjectile.hpp
        src/systems/icePickSystem.cpp
        src/systems/icePickSystem.hpp)

if (IS_OS_MAC)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif ()
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC src/)

# Added this so policy CMP0065 doesn't scream
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS 0)

# External header-only libraries in the ext/

target_include_directories(${PROJECT_NAME} PUBLIC ext/stb_image/)
target_include_directories(${PROJECT_NAME} PUBLIC ext/gl3w)
target_include_directories(${PROJECT_NAME} PUBLIC ext/freetype)

# add external lib json parser
target_include_directories(${PROJECT_NAME} PUBLIC ext/nlohmann/)

# Find OpenGL
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})
endif ()

# glfw, sdl could be precompiled (on windows) or installed by a package manager (on OSX and Linux)

if (IS_OS_LINUX OR IS_OS_MAC)
    # Try to find packages rather than to use the precompiled ones
    # Since we're on OSX or Linux, we can just use pkgconfig.
    find_package(PkgConfig REQUIRED)
    find_package(freetype REQUIRED)

    pkg_search_module(GLFW REQUIRED glfw3)

    pkg_search_module(SDL2 REQUIRED sdl2)
    pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
    pkg_search_module(FT2 REQUIRED Freetype2)

    # Link Frameworks on OSX
    if (IS_OS_MAC)
        find_library(COCOA_LIBRARY Cocoa)
        find_library(CF_LIBRARY CoreFoundation)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${COCOA_LIBRARY} ${CF_LIBRARY})
    endif ()
elseif (IS_OS_WINDOWS)
    # https://stackoverflow.com/questions/17126860/cmake-link-precompiled-library-depending-on-os-and-architecture
    set(GLFW_FOUND TRUE)
    set(SDL2_FOUND TRUE)
    set(FT2_FOUND TRUE)

    set(GLFW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/include")
    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/include/SDL")
    set(FT2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/include")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
        set(GLFW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3dll-x64.lib")
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x64.lib")
        set(SDL2MIXER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x64.lib")
        set(FT2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win86/freetype.lib")

        set(GLFW_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3-x64.dll")
        set(SDL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x64.dll")
        set(SDLMIXER_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x64.dll")
        set(FT2_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win86/freetype.dll")
    else ()
        set(GLFW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3dll-x86.lib")
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x86.lib")
        set(SDL2MIXER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x86.lib")
        set(FT2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win86/freetype.lib")

        set(GLFW_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3-x86.dll")
        set(SDL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x86.dll")
        set(SDLMIXER_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x86.dll")
        set(FT2_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win86/freetype.dll")
    endif ()

    # Copy and rename dlls
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLFW_DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/glfw3.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDLMIXER_DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2_mixer.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FT2_DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Freetype.dll")
endif ()

# Can't find the include and lib. Quit.
if (NOT GLFW_FOUND OR NOT SDL2_FOUND)
    if (NOT GLFW_FOUND)
        message(FATAL_ERROR "Can't find GLFW.")
    elseif (NOT SDL2_FOUND)
        message(FATAL_ERROR "Can't find SDL.")
    elseif (NOT FT2_FOUND)
        message(FATAL_ERROR "Can't find Freetype.")
    endif ()
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${FT2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${GLFW_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${SDL2MIXER_LIBRARIES}
        ${FT2_LIBRARIES})

# Needed to add this
if (IS_OS_LINUX)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS})
endif ()
