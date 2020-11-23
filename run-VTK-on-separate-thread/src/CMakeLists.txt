set(HEADERS
#	
)

set(SOURCES
#
)

	add_executable(a.out main.cpp ${SOURCES} ${HEADERS})
	target_link_libraries(a.out
		${VTK_LIBRARIES}

)

