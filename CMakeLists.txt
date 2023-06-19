cmake_minimum_required(VERSION 3.5)

project(FileDialog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
    Quick
    QuickControls2
)

set(CPP_SOURCE
    src/c++/main.cpp
    src/c++/filesystemmodel.h src/c++/filesystemmodel.cpp
)
set(RESOURCES_SOURCE
    src/resources/resources.qrc
)
set(QML_SOURCE
    src/qml/qml.qrc
)

add_executable(${PROJECT_NAME} ${CPP_SOURCE} ${RESOURCES_SOURCE} ${QML_SOURCE})


target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
)

add_subdirectory(libs)

execute_process(COMMAND git describe --tags --always WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CMAKE_COMMAND} -E env TZ=UTC git log -1 --format=%cd --date=format-local:"%d.%m.%Y %H:%M:%S" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_SOURCE_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
string(TIMESTAMP PROJECT_BUILD_DATE "%d.%m.%Y %H:%M:%S" UTC)
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}" -DPROJECT_VERSION="${GIT_VERSION}" -DPROJECT_SOURCE_DATE=${GIT_SOURCE_DATE} -DPROJECT_BUILD_DATE="${PROJECT_BUILD_DATE}")
