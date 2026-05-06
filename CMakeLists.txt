cmake_minimum_required(VERSION 3.16)

project(ProcPanel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Charts)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appProcPanel
    main.cpp
)

qt_add_qml_module(appProcPanel
    URI ProcPanel
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES procmanager.h procmanager.cpp
        SOURCES processmodel.h processmodel.cpp
        QML_FILES Details.qml
        QML_FILES Overview.qml
        SOURCES resourceusage.h resourceusage.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appProcPanel PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appProcPanel
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appProcPanel
    PRIVATE Qt6::Quick Qt6::Charts
)

install(TARGETS appProcPanel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)