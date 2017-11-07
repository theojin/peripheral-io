PROJECT(peripheral-io-test C)
SET(fw_test "${fw_name}-test")

INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_test} REQUIRED capi-system-info)

FOREACH(flag ${${fw_test}_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH()

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -Wall -fPIE")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -pie")

SET(TEST_INCLUDE_DIR ./include)
INCLUDE_DIRECTORIES(${TEST_INCLUDE_DIR})

AUX_SOURCE_DIRECTORY(src test_sources)
FOREACH(src ${test_sources})
	SET(test_src ${test_src} ${src})
ENDFOREACH()

AUX_SOURCE_DIRECTORY(. sources)
FOREACH(src ${sources})
	GET_FILENAME_COMPONENT(src_name ${src} NAME_WE)
	ADD_EXECUTABLE(${src_name} ${src} ${test_src})
	TARGET_LINK_LIBRARIES(${src_name} ${fw_name} ${${fw_test}_LDFLAGS})
ENDFOREACH()

INSTALL(TARGETS peripheral-io-test RUNTIME DESTINATION bin/)