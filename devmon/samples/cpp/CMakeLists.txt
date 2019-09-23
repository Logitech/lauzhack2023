cmake_minimum_required(VERSION 3.3)

project(demon-test)

# Reconfigure final output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Use C++ 14.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE AND NOT IOS)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Deployment target for OSX" FORCE)
endif()

# Visual Studio Options
if(MSVC)
    # Enable MultiProcessor builds
    add_definitions(/MP)

    # Avoid unnamed objects with custom construction and destruction
    add_definitions(/wd26444)

    # Static link to C Runtime
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if (${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)

endif()

# Windows-specific
if(WIN32)
    add_definitions(-DNOMINMAX)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-D_WIN32_WINNT=0x0601) # For asio
endif()

# JSON library
set(BUILD_TESTING OFF CACHE INTERNAL "")
include_directories(submodules/json/include)

# asio library
include_directories(submodules/asio/asio/include)

# websocketpp library
add_definitions(-DASIO_STANDALONE)
add_definitions(-D_WEBSOCKETPP_CPP11_RANDOM_DEVICE_)
add_definitions(-D_WEBSOCKETPP_CPP11_TYPE_TRAITS_)
include_directories(submodules/websocketpp)

# Google test library
add_subdirectory(submodules/googletest)

# Source code
add_subdirectory(src)
