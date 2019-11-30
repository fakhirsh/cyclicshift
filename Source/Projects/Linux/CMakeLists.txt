cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME CyclicShift)

project (${PROJECT_NAME})

option(USING_LINUX "Using Linux, certain libraries should be enabled/disabled" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../../Game/Linux)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# https://stackoverflow.com/questions/7031126/switching-between-gcc-and-clang-llvm-using-cmake
#set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE string "clang compiler" FORCE)
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE string "clang++ compiler" FORCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )

# Remember to specify the path within quotes " "
include_directories("../../FEngine")

CONFIGURE_FILE(../../../Assets/Development/Config/SystemConfig.xml ../../Game/Linux/Data/Config/SystemConfig.xml COPYONLY)

CONFIGURE_FILE(../../../Assets/Development/Effects/GL30/SimpleVertex2D.vs ../../Game/Linux/Data/Effects/GL30/SimpleVertex2D.vs COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Effects/GL30/SimpleVertex2D.fs ../../Game/Linux/Data/Effects/GL30/SimpleVertex2D.fs COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Effects/GL30/TexturedVertex.vs ../../Game/Linux/Data/Effects/GL30/TexturedVertex.vs COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Effects/GL30/TexturedVertex.fs ../../Game/Linux/Data/Effects/GL30/TexturedVertex.fs COPYONLY)

#CONFIGURE_FILE(../../../Assets/Development/Textures/player.png ../../Game/Linux/Data/Textures/player.png COPYONLY)
#CONFIGURE_FILE(../../../Assets/Development/Textures/enemyShip.png ../../Game/Linux/Data/Textures/enemyShip.png COPYONLY)
#CONFIGURE_FILE(../../../Assets/Development/Textures/enemyUFO.png ../../Game/Linux/Data/Textures/enemyUFO.png COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Textures/zombie.png ../../Game/Linux/Data/Textures/zombie.png COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Textures/zombie.xml ../../Game/Linux/Data/Textures/zombie.xml COPYONLY)

CONFIGURE_FILE(../../../Assets/Development/Actors/player.xml ../../Game/Linux/Data/Actors/player.xml COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Actors/enemy.xml ../../Game/Linux/Data/Actors/enemy.xml COPYONLY)

#CONFIGURE_FILE(../../../Assets/Development/Sounds/gameplayMusic.ogg ../../Game/Linux/Data/Sounds/gameplayMusic.ogg COPYONLY)

add_custom_command(
        TARGET foo POST_BUILD
        COMMAND ${CMAKE_COMMAND} copy
                ${CMAKE_BINARY_DIR}/compile_commands.json
                ../../compile_commands.json)


add_custom_target(foo)


add_subdirectory(../../FEngine ${CMAKE_BINARY_DIR}/FEngine)

set ( HDR

    )

set ( SRC
        main.cpp
    )
	
# Executable
add_executable(${PROJECT_NAME}
                ${HDR} 
                ${SRC} 
            )


target_link_libraries(${PROJECT_NAME} 
                            FEngine
                     )

