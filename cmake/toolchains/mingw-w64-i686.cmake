set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

# Homebrew mingw-w64 on macOS typically provides this target prefix.
set(TOOLCHAIN_PREFIX i686-w64-mingw32 CACHE STRING "MinGW-w64 toolchain prefix")

set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}-g++")
set(CMAKE_RC_COMPILER "${TOOLCHAIN_PREFIX}-windres")
