cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME 3DProcGen)

project (${PROJECT_NAME})

# Remember to specify the path within quotes " "
include_directories("../../3rdParty/glm-0.9.8.1")
include_directories("../../3rdParty/glfw-3.1.2/include")
include_directories("../../3rdParty/glew-1.13.0/include")

CONFIGURE_FILE(../../../Assets/Config/SystemConfig.xml Assets/Config/SystemConfig.xml COPYONLY)
CONFIGURE_FILE(../../../Assets/Effects/SimpleShader.vs Assets/Effects/SimpleShader.vs COPYONLY)
CONFIGURE_FILE(../../../Assets/Effects/SimpleShader.fs Assets/Effects/SimpleShader.fs COPYONLY)

add_subdirectory(../../3rdParty/glew-1.13.0 ${CMAKE_BINARY_DIR}/glew)
add_subdirectory(../../3rdParty/glfw-3.1.2 ${CMAKE_BINARY_DIR}/glfw)


set ( HDR
        ../../FEngine/Renderer/GL30/Program.hpp
        ../../FEngine/Renderer/GL30/SimpleVertex2DProgram.hpp
    )

set ( SRC
        main.cpp
        ../../FEngine/Renderer/GL30/Program.cpp
        ../../FEngine/Renderer/GL30/SimpleVertex2DProgram.cpp
    )
	
# Executable
add_executable(${PROJECT_NAME}
                ${HDR} 
                ${SRC} 
            )


target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES} GLEW)

