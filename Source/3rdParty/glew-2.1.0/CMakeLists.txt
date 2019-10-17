cmake_minimum_required (VERSION 2.8)

set ( HDR
    )

set ( SRC
        src/glew.c
    )
	
ADD_LIBRARY(GLEW STATIC
		${HDR}
		${SRC}
)

