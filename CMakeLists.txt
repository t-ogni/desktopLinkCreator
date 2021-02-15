cmake_minimum_required(VERSION 3.4)
project(desktopLinkCreator)

set(CMAKE_CXX_STANDARD 17)


add_executable(desktopLinkCreator main.cpp)

set(QT_VERSION 5)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(REQUIRED_LIBS Core Gui Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
