cmake_minimum_required(VERSION 3.5)

project(centurioncoin)

option(BUILD_GUI "Build GUI" ON)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -fpermissive") # remove -w

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED COMPONENTS system filesystem program_options thread)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${OpenSSL_INCLUDE_DIRS} ${Miniupnpc_INCLUDE_DIRS})
link_directories("src/leveldb")
set(CORE_LIBS
    leveldb memenv rt db_cxx miniupnpc qrencode
    Boost::system Boost::filesystem Boost::program_options Boost::thread 
    ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY}
)

include_directories("src" "src/json" "src/leveldb/include" "src/leveldb/helpers")
aux_source_directory("src" CORE_SOURCES)
aux_source_directory("src/zerocoin" ZEROCOIN_SOURCES)
set(CORE_SOURCES ${CORE_SOURCES} ${ZEROCOIN_SOURCES})

if(BUILD_GUI)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    find_package(Qt5Widgets REQUIRED)

    include_directories("src/qt")
    file(GLOB GUI_SOURCES "src/qt/*.cpp")
    file(GLOB GUI_RC_SOURCES "src/qt/*.qrc")
    file(GLOB GUI_UI_SOURCES "src/qt/forms/*.ui")
    qt5_wrap_ui(GUI_GENERATED_HEADERS ${GUI_UI_SOURCES})

    set(GUI_SOURCES ${GUI_SOURCES} ${GUI_RC_SOURCES} ${GUI_GENERATED_HEADERS})
    
    if(APPLE)
        set(GUI_SOURCES ${GUI_SOURCES} "src/qt/macdockiconhandler.mm")
    endif()

    add_executable(centurion-qt ${CORE_SOURCES} ${GUI_SOURCES})
    target_link_libraries(centurion-qt ${CORE_LIBS} Qt5::Widgets)
    target_compile_definitions(centurion-qt PRIVATE -DQT_GUI)

    set_target_properties(centurion-qt PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/src/qt"
    )
endif(BUILD_GUI)

if(BUILD_TESTS)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)

    aux_source_directory("src/test" TEST_SOURCES)
    # set(TEST_SOURCES "src/test/test_bitcoin.cpp") # only main file for testing

    add_executable(test_centurion ${CORE_SOURCES} ${TEST_SOURCES})
    target_link_libraries(test_centurion ${CORE_LIBS} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    target_compile_definitions(test_centurion PRIVATE -DBUILD_TESTS)

    set_target_properties(test_centurion PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/src/test"
    )
endif(BUILD_TESTS)
