pkg_check_modules(MIRTEST mirtest>=0.26 REQUIRED)

include_directories(
    SYSTEM
    ${MIRTEST_INCLUDE_DIRS}
    ${MIRAL_INCLUDE_DIRS}
    ${libunity8-private_SOURCE_DIR}
)

set(FakeUnityApplicationQml_SOURCES
    plugin.cpp
    ApplicationInfo.cpp
    ApplicationManager.cpp
    MirSurface.cpp
    MirSurfaceItem.cpp
    MirSurfaceListModel.cpp
    MirMock.cpp
    ObjectListModel.h
    SurfaceManager.cpp
    VirtualKeyboard.cpp
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/ApplicationInfoInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/ApplicationManagerInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/Mir.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/MirSurfaceInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/MirSurfaceItemInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/MirSurfaceListInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/SurfaceManagerInterface.h
    resources/surfaces.qrc
)

add_library(FakeUnityApplicationQml MODULE
    ${FakeUnityApplicationQml_SOURCES}
)

#add_dependencies(FakeUnityApplicationQml windowmanagementpolicy)

target_link_libraries(FakeUnityApplicationQml
    ${MIRTEST_LDFLAGS}
    ${MIRAL_LDFLAGS}
    mockwindowmanagmentpolicy
)

add_library(NonMirUnityApplicationQml MODULE ${FakeUnityApplicationQml_SOURCES})
set_target_properties(NonMirUnityApplicationQml PROPERTIES OUTPUT_NAME FakeUnityApplicationQml)

target_link_libraries(NonMirUnityApplicationQml
    ${MIRTEST_LDFLAGS}
    ${MIRAL_LDFLAGS}
    mockwindowmanagmentpolicy
    Qt5::Core Qt5::Quick Qt5::DBus
)

target_link_libraries(FakeUnityApplicationQml Qt5::Core Qt5::Quick Qt5::DBus)

add_unity8_mock(Unity.Application 0.1 Unity/Application TARGETS FakeUnityApplicationQml)
add_unity8_mock(Unity.Application 0.1 Unity/Application
                PREFIX nonmirplugins
                TARGETS NonMirUnityApplicationQml
                BINARY_DIR ${CMAKE_BINARY_DIR}/nonmirplugins
                NO_TYPES)
