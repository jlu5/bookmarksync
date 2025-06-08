cmake_minimum_required(VERSION 3.16)
project(bookmarksync LANGUAGES CXX)
add_subdirectory(src)

install(FILES bookmarksync.desktop
        DESTINATION share/applications)
install(FILES bookmarksync.svg
        DESTINATION share/icons/hicolor/scalable/apps)
