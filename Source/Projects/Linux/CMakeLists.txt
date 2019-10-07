cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME CyclicShift)

project (${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../../Game/Linux)

# Remember to specify the path within quotes " "
include_directories("../../FEngine")

CONFIGURE_FILE(../../../Assets/Release/Config/SystemConfig.xml ../../Game/Linux/Data/Config/SystemConfig.xml COPYONLY)
#CONFIGURE_FILE(../../../Assets/Release/Effects/SimpleShader.vs ../../Game/Linux/Data/Effects/SimpleShader.vs COPYONLY)
#CONFIGURE_FILE(../../../Assets/Release/Effects/SimpleShader.fs ../../Game/Linux/Data/Effects/SimpleShader.fs COPYONLY)

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

