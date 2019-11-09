cmake_minimum_required(VERSION 2.8)

set (PROJECT_NAME AtlasMaker)

project (${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../../Bin/Linux)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# https://stackoverflow.com/questions/7031126/switching-between-gcc-and-clang-llvm-using-cmake
#set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE string "clang compiler" FORCE)
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE string "clang++ compiler" FORCE)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )

CONFIGURE_FILE(../../../Assets/listdir.py ../../Bin/Linux/Assets/listdir.py COPYONLY)
CONFIGURE_FILE(../../../Assets/SystemConfig.xml ../../Bin/Linux/Assets/SystemConfig.xml COPYONLY)

include_directories(../../../../../Source/FEngine/)

include_directories(../../../../../Source/3rdParty/tinyxml2)
include_directories(../../../../../Source/3rdParty/glm-0.9.8.1)
include_directories(../../../../../Source/3rdParty/RectangleBinPack)
include_directories(../../../../../Source/3rdParty/libpng-1.6.15)

add_subdirectory(../../../../../Source/FEngine/ ${CMAKE_BINARY_DIR}/FEngine)

#############################################################
# ALREADY ADDED IN FENGINE... NO NEED TO ADD AGAIN !!!
#############################################################
#add_subdirectory(../../../../../Source/3rdParty/tinyxml2 ${CMAKE_BINARY_DIR}/tinyxml2)
#add_subdirectory(../../../3rdParty/libpng-1.6.15 ${CMAKE_BINARY_DIR}/libpng)
#add_subdirectory(../../../3rdParty/RectangleBinPack ${CMAKE_BINARY_DIR}/RectangleBinPack)

set ( HDR
        ../../Common/Support.hpp
        ../../Common/System.hpp
	)

set ( SRC
        ../../Common/System.cpp
        main.cpp
	)


# Executable
add_executable(${PROJECT_NAME}
                ${HDR} 
                ${SRC} 
            )

	
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                        FEngine
                       )
                       


