cmake_minimum_required(VERSION 3.16)
project(bookmarksync VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(KF6KIO)
find_package(KF6IconThemes)
qt_standard_project_setup()

qt_add_executable(bookmarksync WIN32 MACOSX_BUNDLE
    backendwidget.cpp backendwidget.h backendwidget.ui
    bookmarksync.cpp bookmarksync.h bookmarksync.ui
    bookmarksyncbackend.cpp bookmarksyncbackend.h
    bookmarksyncgtkbackend.cpp bookmarksyncgtkbackend.h
    bookmarksynckdebackend.cpp bookmarksynckdebackend.h
    bookmarksyncqtbackend.cpp bookmarksyncqtbackend.h
    kdeplacefilterproxymodel.cpp kdeplacefilterproxymodel.h
    main.cpp
    place.h
    placeeditdialog.cpp placeeditdialog.h placeeditdialog.ui
    placesitemmodel.cpp placesitemmodel.h
)
target_compile_definitions(bookmarksync PRIVATE
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(bookmarksync PRIVATE
    KF6::KIOCore KF6::KIOFileWidgets KF6::KIOWidgets KF6::IconThemes
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS bookmarksync
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET bookmarksync
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
