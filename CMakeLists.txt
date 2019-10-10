cmake_minimum_required(VERSION 3.13)

project(gitstats LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    src/repo.cpp
    src/commitsbyauthor.cpp
    src/commitsperday.cpp
)

set(HEADERS
    src/repo.h
    src/commithandler.h
    src/commitsbyauthor.h
    src/commitsperday.h
)

set(RESOURCES
  qml.qrc
)

add_subdirectory(libgit2)

if (WIN32)
  set(Qt5_DIR "C:/Qt/5.13.1/mingw73_64/lib/cmake/Qt5")
endif()
find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

get_target_property(GIT_INCLUDE git2internal INCLUDE_DIRECTORIES)

add_executable(gitstats ${SOURCES} ${HEADERS} ${RESOURCES})
target_include_directories(gitstats PRIVATE ${GIT_INCLUDE})
target_compile_definitions(gitstats
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(gitstats
  PRIVATE git2 Qt5::Core Qt5::Quick Qt5::Gui Qt5::Qml Qt5::Network Qt5::Widgets tbb)

message(STATUS "TEST: ${LIBGIT2_INCLUDES}")


if (WIN32)
  add_custom_command(TARGET gitstats POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:git2> ${CMAKE_BINARY_DIR}
    COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:Qt5::Core> ${CMAKE_BINARY_DIR}
    COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:Qt5::Gui> ${CMAKE_BINARY_DIR}
    COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:Qt5::Quick> ${CMAKE_BINARY_DIR}
    COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:Qt5::Qml> ${CMAKE_BINARY_DIR}
    COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:Qt5::Network> ${CMAKE_BINARY_DIR}
    COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:Qt5::Widgets> ${CMAKE_BINARY_DIR}
  )  
endif()
