cmake_minimum_required(VERSION 3.7)

## Load CMAKE configuration from environment variables
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})

set(CMAKE_DEBUG_POSTFIX d)

## Set the project name
set(PROJECT_NAME Zip)

## Set the lib name
## Specify a name for the generated executable file
set(MAIN_LIB_NAME ${PROJECT_NAME})

## The folder name for a libraries used.
set(EXAMPLES_FOLDER_NAME Examples)
set(LIBS_FOLDER_NAME Libs)

## Enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
                       
## Specify a project name
project(${PROJECT_NAME})

## Set the build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" 
       CACHE STRING "Build configuration 'Release' or 'Debug'."
       FORCE)
endif()

## Install the executable to <install_directory>/bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

## Install libraries (if any) to <install_directory>/bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

option(ZIP_BUILD_EXAMPLES "Build zip examples?" OFF)

add_subdirectory(Source)
if(${ZIP_BUILD_EXAMPLES})
	add_subdirectory(Examples)
endif()
add_subdirectory(ThirdParty)