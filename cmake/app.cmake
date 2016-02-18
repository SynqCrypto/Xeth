find_package(Qt5 COMPONENTS Core Widgets WebKit WebKitWidgets Concurrent REQUIRED)
find_package(JsonCPP REQUIRED)
find_package(Boost COMPONENTS system filesystem thread program_options random regex date_time REQUIRED)
find_package(LevelDB REQUIRED)
find_package(LibScrypt REQUIRED)


set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

set(APP_SOURCES src/main.cpp src/Application.cpp src/window/Window.cpp)


include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/libethrpc/include
    ${PROJECT_BINARY_DIR}/libethkey/include
    ${PROJECT_BINARY_DIR}/libethstealth/include
)



add_executable(xeth ${APP_SOURCES} resources/icon.qrc resources/css.qrc resources/js.qrc resources/html.qrc resources/template.qrc)

target_link_libraries(xeth
    xethlib
    ethstealth
    ethrpc
    ethkey
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Core_LIBRARIES}
    ${JSONCPP_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_RANDOM_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${CRYPTOPP_LIBRARY}
    ${LIBSCRYPT_LIBRARY}
    ${LEVELDB_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    gmp
)



