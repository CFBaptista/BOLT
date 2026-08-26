if(NOT ENABLE_COVERAGE)
    return()
endif()

if(NOT BUILD_TESTING)
    message(WARNING "ENABLE_COVERAGE requires BUILD_TESTING=ON")
    return()
endif()

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "^(Clang|AppleClang|GNU)$")
    message(WARNING "Code coverage is only supported for LLVM and GNU compilers (found: ${CMAKE_CXX_COMPILER_ID})")
    return()
endif()

include(cmake/scripts/coverage_target.cmake)

bolt_register_for_coverage(compile_settings)

cmake_language(DEFER CALL _bolt_create_coverage_target)
