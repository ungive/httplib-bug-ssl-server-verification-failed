cmake_minimum_required(VERSION 3.20)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32 AND MSVC)
    add_compile_options(/Zc:__cplusplus /EHsc)
endif()

add_executable(main main.cpp)

find_package(OpenSSL REQUIRED)
target_link_libraries(main OpenSSL::SSL OpenSSL::Crypto)

set(HTTPLIB_USE_OPENSSL_IF_AVAILABLE true CACHE BOOL "" FORCE)
set(HTTPLIB_USE_WOLFSSL_IF_AVAILABLE false CACHE BOOL "" FORCE)
set(HTTPLIB_USE_MBEDTLS_IF_AVAILABLE false CACHE BOOL "" FORCE)
set(HTTPLIB_USE_ZLIB_IF_AVAILABLE false CACHE BOOL "" FORCE)
set(HTTPLIB_USE_BROTLI_IF_AVAILABLE false CACHE BOOL "" FORCE)
set(HTTPLIB_USE_ZSTD_IF_AVAILABLE false CACHE BOOL "" FORCE)
add_subdirectory(cpp-httplib EXCLUDE_FROM_ALL)
target_link_libraries(main httplib::httplib)
target_compile_definitions(main PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)

if(WIN32)
    if(DEFINED CONAN_RUNTIME_LIB_DIRS)
        foreach(CONAN_RUNTIME_LIB_DIR ${CONAN_RUNTIME_LIB_DIRS})
            # Install the DLLs in a known location, so that they can be
            # installed with the install() command. The generator expression
            # below cannot be used with that unfortunately.
            add_custom_command(
                TARGET main
                POST_BUILD
                COMMAND ${CMAKE_COMMAND}
                    -DSRC_DIR=${CONAN_RUNTIME_LIB_DIR}
                    -DDEST_DIR=${CMAKE_CURRENT_BINARY_DIR}/runtime_dlls
                    -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/copy_dlls.cmake"
                VERBATIM)
            # Make sure we can debug and test the application by copying
            # the DLLs to the application's target file directory.
            add_custom_command(
                TARGET main
                POST_BUILD
                COMMAND ${CMAKE_COMMAND}
                    -DSRC_DIR=${CONAN_RUNTIME_LIB_DIR}
                    -DDEST_DIR=$<TARGET_FILE_DIR:main> -DQUIET=1
                    -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/copy_dlls.cmake"
                VERBATIM)
        endforeach()
        install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/runtime_dlls/libcrypto-3-x64.dll
            ${CMAKE_CURRENT_BINARY_DIR}/runtime_dlls/libssl-3-x64.dll
            DESTINATION .)
    else()
        message(FATAL_ERROR "Missing CONAN_RUNTIME_LIB_DIRS")
    endif()
endif()
