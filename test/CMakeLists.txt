SET(fw_test "vpn_setting_test")

SET(dependents "capi-base-common glib-2.0")

INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_test} REQUIRED ${dependents})
FOREACH(flag ${${fw_test}_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -Wall -fPIE")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -pie")

aux_source_directory(. sources)
FOREACH(src ${sources})
    GET_FILENAME_COMPONENT(src_name ${src} NAME_WE)
    MESSAGE("${fw_test}")
    ADD_EXECUTABLE(${fw_test} ${src})
    TARGET_LINK_LIBRARIES(${fw_test} ${fw_name} ${${fw_test}_LDFLAGS})
    INSTALL(TARGETS ${fw_test} DESTINATION ${LIB_INSTALL_DIR}/vpn_setting_test/)
    INSTALL(TARGETS ${fw_test} RUNTIME DESTINATION bin/)
ENDFOREACH()
