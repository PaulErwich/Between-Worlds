cmake_minimum_required(VERSION 3.14)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h
        src/GameStates/State.h src/GameStates/GameStateBase.cpp src/GameStates/GameStateBase.h
        src/Other/GameData.h src/GameStates/GameMenu.cpp src/GameStates/GameMenu.h
        src/GameStates/GameLobby.cpp src/GameStates/GameLobby.h
        src/GameStates/GameLevelSelect.cpp src/GameStates/GameLevelSelect.h
        src/GameStates/GamePlay.cpp src/GameStates/GamePlay.h
        src/GameStates/GameWin.cpp src/GameStates/GameWin.h
        src/GameStates/GameOver.cpp src/GameStates/GameOver.h
        src/GameObjects/GameObject.h src/GameObjects/GameObject.cpp
        src/Networking/CustomPacket.h src/Networking/CustomPacket.cpp
        src/tinyxml2/tinyxml2.h src/tinyxml2/tinyxml2.cpp
        src/LevelLoading/LevelData.h src/LevelLoading/LevelData.cpp src/Networking/PacketType.h src/Networking/SFMLPacketOverloads.h src/Other/Helper.h src/Other/AnimationHelper.h src/Other/AnimationState.h
        src/LevelLoading/LevelData.h src/LevelLoading/LevelData.cpp
        src/Networking/PacketType.h src/Networking/PacketType.cpp
        src/Networking/SFMLPacketOverloads.h src/Networking/SFMLPacketOverloads.cpp
        src/Networking/Client.cpp src/Networking/Client.h
        src/GameObjects/Switch.cpp src/GameObjects/Switch.h
        src/Networking/Server.cpp src/Networking/Server.h
        src/GameObjects/Character.cpp src/GameObjects/Character.h
        src/LevelLoading/LevelData.h src/LevelLoading/LevelData.cpp
        src/Other/Helper.h
        src/Other/AnimationHelper.h src/Other/AnimationState.h src/GameObjects/Puzzle.cpp src/GameObjects/Puzzle.h src/Networking/ServerData.h src/Other/ControlledPlayer.h
        src/Other/AnimationHelper.h src/Other/AnimationState.h
        src/GameObjects/Collectible.h src/GameObjects/Collectible.cpp src/LevelLoading/Tile.h src/LevelLoading/Tile.cpp
        src/GameObjects/Collectible.h src/GameObjects/Collectible.cpp
         src/GameObjects/Character.cpp src/GameObjects/Character.h
         src/GameObjects/Door.cpp src/GameObjects/Door.h src/GameObjects/PuzzlePiece.cpp src/GameObjects/PuzzlePiece.h
        src/Camera/Camera.cpp src/Camera/Camera.h src/GameObjects/Pressureplate.cpp src/GameObjects/Pressureplate.h
         src/GameObjects/PushableObject.h src/GameObjects/PushableObject.cpp src/GameObjects/Portal.cpp src/GameObjects/Portal.h)

add_executable(SFMLGame ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (SFMLGame ${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib)
target_link_libraries (SFMLGame ${CMAKE_SOURCE_DIR}/lib/sfml-audio.lib)
target_link_libraries (SFMLGame ${CMAKE_SOURCE_DIR}/lib/sfml-network.lib)
target_link_libraries (SFMLGame ${CMAKE_SOURCE_DIR}/lib/sfml-system.lib)
target_link_libraries (SFMLGame ${CMAKE_SOURCE_DIR}/lib/sfml-window.lib)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/DLL/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(my_custom_target
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Data/Shaders/portaly.glsl ${CMAKE_CURRENT_BINARY_DIR}/Data/Shaders/portaly.glsl
        DEPENDS ${CMAKE_SOURCE_DIR}/Data/Shaders/portaly.glsl
        COMMENT "Copying portaly.glsl to build directory"
        )
