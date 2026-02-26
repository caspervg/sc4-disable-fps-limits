cmake_minimum_required(VERSION 3.24)

project(
    SC4DisableFpsLimits
    VERSION 0.1.1
    LANGUAGES CXX
)

if (NOT WIN32)
    message(FATAL_ERROR
        "Only Windows x86 builds are supported. "
        "Use 'vs2022-win32' on Windows or 'mingw-win32-cross' from macOS/Linux.")
endif ()

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    if (MSVC)
        message(FATAL_ERROR "SimCity 4 plugins must be 32-bit. Reconfigure with: cmake -A Win32 ...")
    else ()
        message(FATAL_ERROR "SimCity 4 plugins must be 32-bit. Use a 32-bit Windows cross toolchain.")
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
enable_language(RC)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/gzcom-dll/gzcom-dll/include/cIGZCOM.h")
    message(
        FATAL_ERROR
        "Missing vendor/gzcom-dll headers. Initialize submodules with: "
        "'git submodule update --init --recursive'."
    )
endif ()

set(SPDLOG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include")
if (NOT EXISTS "${SPDLOG_INCLUDE_DIR}/spdlog/spdlog.h")
    message(
        FATAL_ERROR
        "Missing vendor/spdlog headers. Initialize submodules with: "
        "'git submodule update --init --recursive'."
    )
endif ()

set(MINI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/mINI/src")
if (NOT EXISTS "${MINI_INCLUDE_DIR}/mini/ini.h")
    message(
        FATAL_ERROR
        "Missing vendor/mINI headers. Initialize submodules with: "
        "'git submodule update --init --recursive'."
    )
endif ()

add_subdirectory(vendor/gzcom-dll)

add_library(
    SC4DisableFpsLimits
    SHARED
    src/DisableFpsLimitsDllDirector.cpp
    src/Logger.cpp
    src/SC4VersionDetection.cpp
    src/Settings.cpp
    src/version.rc
)

target_include_directories(
    SC4DisableFpsLimits
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/gzcom-dll/gzcom-dll/include
        ${SPDLOG_INCLUDE_DIR}
        ${MINI_INCLUDE_DIR}
)

target_compile_definitions(
    SC4DisableFpsLimits
    PRIVATE
        UNICODE
        _UNICODE
        WIN32
        _WINDOWS
        _USRDLL
)

target_link_libraries(SC4DisableFpsLimits PRIVATE gzcom_dll version)

set_target_properties(SC4DisableFpsLimits PROPERTIES OUTPUT_NAME "SC4DisableFpsLimits")

if (MSVC)
    target_compile_options(
        gzcom_dll
        PRIVATE
            /W3
            /EHsc
            /utf-8
            /permissive-
    )
    target_compile_options(
        SC4DisableFpsLimits
        PRIVATE
            /W3
            /EHsc
            /utf-8
            /permissive-
    )
endif ()
