set(LIB_NAME "unity8-private")
set(SOVERSION 0)
set(VERSION ${SOVERSION}.0.0)

project(lib${LIB_NAME})

set(lib${LIB_NAME}_SRCS
    abstractdbusservicemonitor.cpp
    unitydbusobject.cpp
    unitydbusvirtualobject.cpp
    wmpolicyinterface.cpp
    )

add_library(${LIB_NAME} SHARED
    ${lib${LIB_NAME}_SRCS}
    )

set_target_properties(${LIB_NAME} PROPERTIES
    VERSION ${VERSION}
    SOVERSION ${SOVERSION}
    )

target_link_libraries(${LIB_NAME} Qt5::DBus)

# install library
install(TARGETS ${LIB_NAME}
     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
