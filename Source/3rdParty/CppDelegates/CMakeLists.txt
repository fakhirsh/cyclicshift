cmake_minimum_required(VERSION 2.8)


set ( HDR
        Delegate.hpp
	)
	
set ( SRC

	)

ADD_LIBRARY(CppDelegates STATIC
		${HDR}
		${SRC}
	)
