CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(project_prefix "capi")
SET(prefix "/usr")
SET(libdir ${LIB_INSTALL_DIR})
SET(version "0.0.1")
SET(service "system")
SET(submodule "peripheral-io")
SET(fw_name "${project_prefix}-${service}-${submodule}")

PROJECT(${fw_name})

SET(dependents "dlog glib-2.0 gio-2.0 gio-unix-2.0 capi-base-common")
SET(pc_dependents "capi-base-common")

SET(CMAKE_INSTALL_PREFIX ${prefix})
SET(PREFIX $(CMAKE_INSTALL_PREFIX))
SET(VERSION ${version})

FIND_PROGRAM(GDBUS_CODEGEN NAMES gdbus-codegen)
EXEC_PROGRAM(${GDBUS_CODEGEN} ARGS
                " \\
                --generate-c-code ${CMAKE_SOURCE_DIR}/src/peripheral_io_gdbus \\
                --c-namespace PeripheralIoGdbus \\
                --interface-prefix org.tizen.peripheral_io. \\
                ${CMAKE_SOURCE_DIR}/src/peripheral_io.xml \\
                ")

SET(INC_DIR include)
INCLUDE_DIRECTORIES(${INC_DIR})

INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_name} REQUIRED ${dependents})
FOREACH(flag ${${fw_name}_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -Wall -Werror -fPIC")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=%{_libdir}")

SET(SOURCES src/peripheral_gpio.c
			src/peripheral_i2c.c
			src/peripheral_pwm.c
			src/peripheral_uart.c
			src/peripheral_spi.c
			src/peripheral_gdbus_gpio.c
			src/peripheral_gdbus_i2c.c
			src/peripheral_gdbus_pwm.c
			src/peripheral_gdbus_uart.c
			src/peripheral_gdbus_spi.c
			src/peripheral_io_gdbus.c
			src/peripheral_spi.c)

ADD_LIBRARY(${fw_name} SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${fw_name} ${${fw_name}_LDFLAGS})

SET_TARGET_PROPERTIES(${fw_name}
	 PROPERTIES
	 VERSION ${FULLVER}
	 SOVERSION ${MAJORVER}
	 CLEAN_DIRECT_OUTPUT 1
)

INSTALL(TARGETS ${fw_name} DESTINATION ${libdir})
INSTALL(
		DIRECTORY ${INC_DIR}/ DESTINATION include
		FILES_MATCHING
		PATTERN "${INC_DIR}/*.h"
		)

SET(PC_NAME ${fw_name})
SET(PC_REQUIRED ${pc_dependents})
SET(PC_LDFLAGS -l${fw_name})

CONFIGURE_FILE(
	${PROJECT_NAME}.pc.in
	${PROJECT_NAME}.pc
	@ONLY
)
INSTALL(FILES ${PROJECT_NAME}.pc DESTINATION ${libdir}/pkgconfig)
