cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME CyclicShift)

project (${PROJECT_NAME})

option(USING_EMSCRIPTEN "Using Emscripten, certain libraries should be enabled/disabled" ON)

SET(CMAKE_EXECUTABLE_SUFFIX ".html")

set(PLATFORM "Emscripten")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../../Game/Emscripten)

################################
#### EXTREMELY IMPORTANT ####
# Current directory is the build dir. It expects to find "Data" dir in this build dir. So we have to adjuct it.
# It can go back/back/forward/forward/back etc etc. At best it can go only a few steps back. So its best to copy the
# assets directory right inside the build folder.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1 -s FULL_ES2=1 --preload-file Data")
################################

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1 -s FULL_ES2=1 --embed-file Data")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s TOTAL_MEMORY=97108864 -s FULL_ES2=1 --preload-file ../../Assets")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1 -s FULL_ES2=1 --embed-file ../../Assets")


# Set include directories
include_directories("../../FEngine")

# Copy all the assets
CONFIGURE_FILE(../../../Assets/Development/Config/SystemConfig.xml Data/Config/SystemConfig.xml COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Effects/GLES20/SimpleVertex2D.vs Data/Effects/GLES20/SimpleVertex2D.vs COPYONLY)
CONFIGURE_FILE(../../../Assets/Development/Effects/GLES20/SimpleVertex2D.fs Data/Effects/GLES20/SimpleVertex2D.fs COPYONLY)

# Add library subdirectories
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

# Link static libraries
target_link_libraries(${PROJECT_NAME}
                        FEngine
					)

