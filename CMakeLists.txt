cmake_minimum_required(VERSION 3.16)

project(lab4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_standard_project_setup()

qt_add_executable(applab4
    main.cpp
)

qt_add_qml_module(applab4
    URI lab4
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES database.h database.cpp listmodel.h listmodel.cpp
    RESOURCES QmlClassDiag.qmodel
    RESOURCES classdiag.qmodel
    RESOURCES variantuse.qmodel
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(applab4 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.applab4
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(applab4
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS applab4
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
