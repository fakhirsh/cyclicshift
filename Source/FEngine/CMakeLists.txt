cmake_minimum_required(VERSION 2.8)

set (PROJECT_NAME FEngine)

project (${PROJECT_NAME})


include_directories("../3rdParty/tinyxml2")


add_subdirectory(../3rdParty/tinyxml2 ${CMAKE_BINARY_DIR}/tinyxml2)


set ( HDR
		System/App.hpp
		ResourceCache/IOManager.hpp
    	ResourceCache/IOManagerDefault.hpp
	)
	
set ( SRC
		System/App.cpp
    	ResourceCache/IOManagerDefault.cpp		
	)

ADD_LIBRARY(FEngine STATIC
		${HDR}
		${SRC}
	)
	
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                       tinyxml2 )
	
