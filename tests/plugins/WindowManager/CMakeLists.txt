include_directories(
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/tests/mocks
    ${libunity8-private_SOURCE_DIR}
    )

add_executable(TopLevelWindowModelTestExec
    tst_TopLevelWindowModel.cpp
    UnityApplicationMocks.h

    ${CMAKE_SOURCE_DIR}/tests/mocks/Unity/Application/MirSurfaceListModel.cpp

    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/ApplicationInfoInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/ApplicationManagerInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/Mir.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/MirSurfaceInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/MirSurfaceListInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/SurfaceManagerInterface.h
    )

target_link_libraries(TopLevelWindowModelTestExec
    Qt5::Test Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick
    windowmanager-qml
    unity8-private
)

install(TARGETS TopLevelWindowModelTestExec
    DESTINATION "${SHELL_PRIVATE_LIBDIR}/tests/plugins/WindowManager"
)

# To find libwindowmanager-qml.so
set_target_properties(TopLevelWindowModelTestExec PROPERTIES
        INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${SHELL_PRIVATE_LIBDIR}")

add_unity8_unittest(TopLevelWindowModel TopLevelWindowModelTestExec
    ENVIRONMENT LD_LIBRARY_PATH=${UNITY_PLUGINPATH}/WindowManager
)
