cmake_minimum_required(VERSION 2.8)

set (PROJECT_NAME FEngine)

project (${PROJECT_NAME})

include_directories("../3rdParty/tinyxml2")
include_directories("../3rdParty/glm-0.9.8.1")
include_directories("../3rdparty/FastDelegate")
if(USING_EMSCRIPTEN)
    # Don't load glfw or glew
else()
    include_directories("../3rdParty/glfw-3.1.2/include")
    include_directories("../3rdParty/glew-1.13.0/include")
endif(USING_EMSCRIPTEN)

add_subdirectory(../3rdParty/tinyxml2 ${CMAKE_BINARY_DIR}/tinyxml2)
if(USING_EMSCRIPTEN)
    # Don't load glfw or glew
else()
    add_subdirectory(../3rdParty/glew-1.13.0 ${CMAKE_BINARY_DIR}/glew)
    add_subdirectory(../3rdParty/glfw-3.1.2 ${CMAKE_BINARY_DIR}/glfw)
endif(USING_EMSCRIPTEN)


set ( HDR
        Debugging/Log.hpp
        Debugging/LogDefault.hpp
		System/App.hpp
		System/WindowManager.hpp
		ResourceCache/IOManager.hpp
    	ResourceCache/IOManagerDefault.hpp
    	Utility/String.hpp
    	Utility/Math.hpp
	)
if(USING_EMSCRIPTEN)
    list ( APPEND HDR 	System/WindowManagerWeb.hpp	)
else()
    list ( APPEND HDR  	System/WindowManagerLinux.hpp )
endif(USING_EMSCRIPTEN)

#message(${HDR})

set ( SRC
		System/App.cpp
    	ResourceCache/IOManagerDefault.cpp
        Debugging/Log.cpp
        Debugging/LogDefault.cpp
       	Utility/String.cpp
    	Utility/Math.cpp
	)

if(USING_EMSCRIPTEN)
    list ( APPEND SRC  System/WindowManagerWeb.cpp )
else()
    list ( APPEND SRC  System/WindowManagerLinux.cpp )
endif(USING_EMSCRIPTEN)

#message(${HDR})

ADD_LIBRARY(FEngine STATIC
		${HDR}
		${SRC}
	)
	
if(USING_EMSCRIPTEN)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                       tinyxml2 
                       )
else()
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                       tinyxml2 
                       glfw 
                       ${OPENGL_glu_LIBRARY} 
                       ${GLFW_LIBRARIES} 
                       GLEW
                       )
endif(USING_EMSCRIPTEN)
