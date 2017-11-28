cmake_minimum_required(VERSION 3.5)

project(centurioncoin)
include(CMakeToolsHelpers OPTIONAL)

option(BUILD_GUI "Build GUI" ON)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DBOOST_SPIRIT_THREADSAFE -DBOOST_THREAD_USE_LIB)

# Core libs
find_package(Boost REQUIRED COMPONENTS system filesystem program_options thread)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
set(LEVELDB_LIBS "${CMAKE_SOURCE_DIR}/src/leveldb/libleveldb.a" "${CMAKE_SOURCE_DIR}/src/leveldb/libmemenv.a")

include_directories(${Boost_INCLUDE_DIRS} ${OpenSSL_INCLUDE_DIRS} ${Miniupnpc_INCLUDE_DIRS})
set(CORE_LIBS
    db_cxx miniupnpc sodium
    Boost::system Boost::filesystem Boost::program_options Boost::thread 
    ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES} ${LEVELDB_LIBS}
)

if(MSYS)
    list(APPEND CORE_LIBS wsock32 ws2_32 shlwapi)
endif()

# Core sources
include_directories("src" "src/json" "src/leveldb/include" "src/leveldb/helpers")
aux_source_directory("src" CORE_SOURCES)
aux_source_directory("src/zerocoin" ZEROCOIN_SOURCES)
set(CORE_SOURCES ${CORE_SOURCES} ${ZEROCOIN_SOURCES})

add_executable(centuriond ${CORE_SOURCES})
target_link_libraries(centuriond ${CORE_LIBS})

if(BUILD_GUI)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5LinguistTools REQUIRED)
    set(GUI_LIBS qrencode)

    include_directories(${Qt5Widgets_INCLUDE_DIRS})


    if(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    endif()
    if(UNIX)
        list(APPEND GUI_LIBS Qt5::Widgets rt)
    endif()

    if(MSYS)
        # MXE workaround: Use pkg-config to find Qt5 libs.
        # https://github.com/mxe/mxe/issues/1642
        find_package(PkgConfig)
        pkg_check_modules(QT5ALL REQUIRED Qt5Widgets)

        list(APPEND GUI_LIBS Qt5::QWindowsIntegrationPlugin)
        list(APPEND GUI_LIBS ${QT5ALL_LDFLAGS})
        
        # Qt5 platform support libs
        list(APPEND GUI_LIBS Qt5EventDispatcherSupport Qt5AccessibilitySupport Qt5FontDatabaseSupport Qt5ThemeSupport freetype bz2 harfbuzz)
    endif()

    include_directories("src/qt")
    file(GLOB GUI_SOURCES "src/qt/*.cpp")
    file(GLOB GUI_RC_SOURCES "src/qt/*.qrc")
    file(GLOB GUI_UI_SOURCES "src/qt/forms/*.ui")
    file(GLOB GUI_TS_SOURCES "src/qt/locale/*.ts")

    qt5_wrap_ui(GUI_UI_HEADERS ${GUI_UI_SOURCES})
    qt5_add_translation(GUI_QM_SOURCES ${GUI_TS_SOURCES})
        
    add_custom_target(gen_translations
	COMMAND ${CMAKE_COMMAND} -E copy ${GUI_QM_SOURCES} "${CMAKE_SOURCE_DIR}/src/qt/locale"
	DEPENDS ${GUI_QM_SOURCES}
	COMMENT "Generating translations files"
    )

    set(GUI_SOURCES ${GUI_SOURCES} ${GUI_RC_SOURCES} ${GUI_UI_HEADERS})

    if(APPLE)
        list(APPEND GUI_SOURCES "src/qt/macdockiconhandler.mm")
    endif()
    
    add_executable(centurion-qt ${CORE_SOURCES} ${GUI_SOURCES} src/qt/res/bitcoin-qt.rc)
    add_dependencies(centurion-qt gen_translations)
    target_link_libraries(centurion-qt ${CORE_LIBS} ${GUI_LIBS})
    target_compile_definitions(centurion-qt PRIVATE -DQT_GUI)

    if(MSYS)
        target_compile_definitions(centurion-qt PRIVATE -DQT_STATICPLUGIN)
    endif()
endif(BUILD_GUI)

if(BUILD_TESTS)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
    set(TEST_LIBS ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    if(MSYS)
        list(APPEND TEST_LIBS iphlpapi)
    endif()

    aux_source_directory("src/test" TEST_SOURCES)

    add_executable(test_centurion ${CORE_SOURCES} ${TEST_SOURCES})
    target_link_libraries(test_centurion ${CORE_LIBS} ${TEST_LIBS})
    target_compile_definitions(test_centurion PRIVATE -DBUILD_TESTS -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK)

    set_target_properties(test_centurion PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/src/test"
    )
endif(BUILD_TESTS)
