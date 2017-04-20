PROJECT(peripheral-io-test C)
SET(fw_test "${fw_name}-test")

INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_test} REQUIRED dlog)
FOREACH(flag ${${fw_test}_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
	MESSAGE(${flag})
ENDFOREACH()

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -Wall")

aux_source_directory(. sources)
FOREACH(src ${sources})
	GET_FILENAME_COMPONENT(src_name ${src} NAME_WE)
	MESSAGE("${src_name}")
	ADD_EXECUTABLE(${src_name} ${src})
	TARGET_LINK_LIBRARIES(${src_name} ${fw_name} ${${fw_test}_LDFLAGS})
ENDFOREACH()

INSTALL(TARGETS peripheral-io-test RUNTIME DESTINATION bin/)