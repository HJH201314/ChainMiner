cmake_minimum_required(VERSION 3.22)

project(ChainMiner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SRC_FILES_DIR
    ${PROJECT_SOURCE_DIR}/ChainMiner/*.cpp
    ${PROJECT_SOURCE_DIR}/ChainMiner/*.hpp
    ${PROJECT_SOURCE_DIR}/ChainMiner/*.h
)

include_directories(
	${CMAKE_SOURCE_DIR}/SDK/include
)
#include_directories(ChainMiner)
link_directories(
	${CMAKE_SOURCE_DIR}/SDK/lib
)

#已在dllmain中引入lib
#link_directories(../SDK/Lib)
#link_libraries(SymDBHelper LiteLoader Chakra bedrock_server_api bedrock_server_var)

add_definitions(
	-D"NDEBUG"
	-D"NOMINMAX"
	-D"TEMPLATE_EXPORTS"
	-D"UNICODE"
	-D"WIN32_LEAN_AND_MEAN"
	-D"_AMD64_"
	-D"_CRT_SECURE_NO_WARNINGS"
	-D"_UNICODE"
	-D"_USRDLL"
	-D"_WINDLL"
	-D"_WINDOWS"
)

add_compile_options(
    /diagnostics:column
    /EHsc
    /FC
    /GL
    /MD
    /nologo
    /permissive-
    /sdl
    /utf-8
    /Zc:inline
    /Zi
)

add_link_options(
    /DEBUG
    /DELAYLOAD:"bedrock_server.dll"
    /DLL
    /IGNORE:4199
    /INCREMENTAL:NO
    /LTCG:INCREMENTAL
    /MANIFESTUAC:NO
    /MACHINE:X64
    /NOLOGO
    /OPT:ICF
    /OPT:REF
    /SUBSYSTEM:CONSOLE
)

add_library(
	${CMAKE_PROJECT_NAME} SHARED ${SRC_FILES_DIR}
)

#设置输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/x64/)
set(TARGET_DIR ${CMAKE_SOURCE_DIR}/x64/Release/)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../BDS-Test/plugins)