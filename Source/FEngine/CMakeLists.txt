cmake_minimum_required(VERSION 2.8)

set (PROJECT_NAME FEngine)

project (${PROJECT_NAME})

include_directories(../3rdParty/tinyxml2)
include_directories(../3rdParty/glm-0.9.8.1)
include_directories(../3rdParty/CppDelegates)
include_directories(../3rdParty/PennerEasing)
include_directories(../3rdParty/RectangleBinPack)
include_directories(../3rdParty/libpng-1.6.15)
include_directories(../3rdParty/libogg-1.3.2/include)
include_directories(../3rdParty/libvorbis-1.3.4/include)

if(USING_EMSCRIPTEN)
    # Don't load glfw or glew
else()
    include_directories("../3rdParty/glfw-3.1.2/include")
    include_directories("../3rdParty/glew-2.1.0/include")
endif(USING_EMSCRIPTEN)

add_subdirectory(../3rdParty/tinyxml2 ${CMAKE_BINARY_DIR}/tinyxml2)
add_subdirectory(../3rdParty/libpng-1.6.15 ${CMAKE_BINARY_DIR}/libpng)
add_subdirectory(../3rdParty/libvorbis-1.3.4 ${CMAKE_BINARY_DIR}/libvorbis)
add_subdirectory(../3rdParty/PennerEasing ${CMAKE_BINARY_DIR}/PennerEasing)
add_subdirectory(../3rdParty/RectangleBinPack ${CMAKE_BINARY_DIR}/RectangleBinPack)

if(USING_EMSCRIPTEN)
    # Don't load glfw or glew
else()
    add_subdirectory(../3rdParty/glew-2.1.0 ${CMAKE_BINARY_DIR}/glew)
    add_subdirectory(../3rdParty/glfw-3.1.2 ${CMAKE_BINARY_DIR}/glfw)
endif(USING_EMSCRIPTEN)


set ( HDR
        ActorManager/Actor.hpp
        ActorManager/ActorFactory.hpp
        ActorManager/Components/Component.hpp
        ActorManager/Components/ComponentFactory.hpp
        ActorManager/Components/KBComponent.hpp
        ActorManager/Components/MouseComponent.hpp
        ActorManager/Components/TransformComponent.hpp
        ActorManager/Components/ViewComponent.hpp
        Debugging/Log.hpp
        Debugging/LogDefault.hpp
        EventManager/Event.hpp
        EventManager/EventManager.hpp
		Graphics2D/Image.hpp
		Graphics2D/PNGImage.hpp
		Graphics2D/Texture.hpp
        System/App.hpp
        System/Definitions.hpp
		System/WindowManager.hpp
		ResourceCache/IOManager.hpp
    	ResourceCache/IOManagerDefault.hpp
        Renderer/Renderer.hpp
        Renderer/Program.hpp
    	Utility/String.hpp
    	Utility/Math.hpp

        TmpGameCode/Game.hpp
	)
if(USING_EMSCRIPTEN)
    list ( APPEND HDR 	System/WindowManagerWeb.hpp	)
    list ( APPEND HDR  	Renderer/GLES20/GLES20Renderer.hpp )
    list ( APPEND HDR  	Renderer/GLES20/SimpleVertex2DProgram.hpp)
    list ( APPEND HDR  	Renderer/GLES20/TexturedVertexProgram.hpp)
else()
    list ( APPEND HDR  	System/WindowManagerLinux.hpp )
    list ( APPEND HDR  	Renderer/GL30/GL30Renderer.hpp )
    list ( APPEND HDR  	Renderer/GL30/SimpleVertex2DProgram.hpp)
    list ( APPEND HDR  	Renderer/GL30/TexturedVertexProgram.hpp)
endif(USING_EMSCRIPTEN)

#message(${HDR})

set ( SRC
        ActorManager/Actor.cpp
        ActorManager/ActorFactory.cpp
        ActorManager/Components/Component.cpp
        ActorManager/Components/ComponentFactory.cpp
        ActorManager/Components/KBComponent.cpp
        ActorManager/Components/MouseComponent.cpp
        ActorManager/Components/TransformComponent.cpp
        ActorManager/Components/ViewComponent.cpp
        EventManager/Event.cpp
        EventManager/EventManager.cpp
		System/App.cpp
		Graphics2D/Image.cpp
		Graphics2D/PNGImage.cpp		
        Graphics2D/Texture.cpp
        ResourceCache/IOManagerDefault.cpp
        Renderer/Renderer.cpp        
        Renderer/Program.cpp
        Debugging/Log.cpp
        Debugging/LogDefault.cpp
       	Utility/String.cpp
    	Utility/Math.cpp

        TmpGameCode/Game.cpp
	)

if(USING_EMSCRIPTEN)
    list ( APPEND SRC  System/WindowManagerWeb.cpp )
    list ( APPEND SRC  	Renderer/GLES20/GLES20Renderer.cpp )
    list ( APPEND SRC  	Renderer/GLES20/SimpleVertex2DProgram.cpp)
    list ( APPEND SRC  	Renderer/GLES20/TexturedVertexProgram.cpp)
else()
    list ( APPEND SRC  System/WindowManagerLinux.cpp )
    list ( APPEND SRC  	Renderer/GL30/GL30Renderer.cpp )
    list ( APPEND SRC  	Renderer/GL30/SimpleVertex2DProgram.cpp)
    list ( APPEND SRC  	Renderer/GL30/TexturedVertexProgram.cpp)
endif(USING_EMSCRIPTEN)

#message(${HDR})

ADD_LIBRARY(FEngine STATIC
		${HDR}
		${SRC}
	)
	
if(USING_EMSCRIPTEN)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                       tinyxml2 
                       png
                       vorbis
					   PennerEasing
					   RectangleBinPack
                       )
else()
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
                       tinyxml2 
                       png
                       vorbis
					   PennerEasing
					   RectangleBinPack
                       glfw 
                       ${OPENGL_glu_LIBRARY} 
                       ${GLFW_LIBRARIES} 
                       GLEW
                       )
endif(USING_EMSCRIPTEN)
