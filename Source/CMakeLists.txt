cmake_minimum_required(VERSION 3.7)

set(ZIP_LIB_NAME Zip)
project(${ZIP_LIB_NAME} VERSION 0.2.3 LANGUAGES C)

## Find all source files to be compiled into object files
file(GLOB_RECURSE ZIP_SOURCES 
	## Main
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

## C++ compiler options
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-Od -Ob0 -MTd")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

## 1. Compile...
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	# large file support
	add_definitions(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64)
endif()

if (MSVC)
  # Use secure functions by default and suppress warnings about "deprecated" functions
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT=1")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D _CRT_NONSTDC_NO_WARNINGS=1 /D _CRT_SECURE_NO_WARNINGS=1")

elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
        "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
        "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
endif (MSVC)

add_library(${ZIP_LIB_NAME} STATIC ${ZIP_SOURCES})
set_target_properties(${ZIP_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${ZIP_LIB_NAME}
	Platform
)

## Sources and headers
target_include_directories(${ZIP_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

## Properties
set_target_properties(${ZIP_LIB_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_compile_options(
    ${ZIP_LIB_NAME} 
	PUBLIC 
    /W3 /nologo /EHsc
    "$<$<CONFIG:Debug>:/MTd;/Od;/Ob0;/Zi;/RTC1;/DDEBUG;/D_DEBUG;>"
    "$<$<CONFIG:Release>:/MT;/O2;/Ob2;/DNDEBUG;>"
)

## 3. Install...
install(TARGETS ${ZIP_LIB_NAME} RUNTIME DESTINATION bin)


