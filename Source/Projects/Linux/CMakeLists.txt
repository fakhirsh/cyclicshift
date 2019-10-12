cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME CyclicShift)

project (${PROJECT_NAME})

option(USING_LINUX "Using Linux, certain libraries should be enabled/disabled" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../../Game/Linux)

# Remember to specify the path within quotes " "
include_directories("../../FEngine")

CONFIGURE_FILE(../../../Assets/Development/Config/SystemConfig.xml ../../Game/Linux/Data/Config/SystemConfig.xml COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Effects/GLES20/SimpleVertex2D.vs ../../Game/Linux/Data/Effects/GLES20/SimpleVertex2D.vs COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Effects/GLES20/SimpleVertex2D.fs ../../Game/Linux/Data/Effects/GLES20/SimpleVertex2D.fs COPYONLY)

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

