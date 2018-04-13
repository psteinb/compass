# cmake compatibility issues
CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

# project name
PROJECT(compass CXX)

# this project is C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckSymbolExists)
include(CheckCXXSourceCompiles)

# Project information
SET (COMPASS_NAME "Compass - drop-in header-only C++ library to detect hardware capabilities at runtime and at compiletime")
SET (COMPASS_CODENAME "${PROJECT_NAME}")
SET (COMPASS_COPYRIGHT_YEARS "2017")
SET (COMPASS_VERSION_MAJOR 0)
SET (COMPASS_VERSION_MINOR 0)
SET (COMPASS_VERSION_PATCH 0)
SET (COMPASS_VERSION "${COMPASS_VERSION_MAJOR}.${COMPASS_VERSION_MINOR}.${COMPASS_VERSION_PATCH}")
SET (COMPASS_VENDOR_ID "psteinb")
SET (COMPASS_ID "${COMPASS_VENDOR_ID}.${PROJECT_NAME}")

option(WITH_CXX11_ABI       "enable _GLIBCXX_USE_CXX11_ABI in GCC 5.0+" ON)
option(WITH_TESTS           "enable unit tests" ON)
option(WITH_SINGLE_HEADER   "use single header file from single-header/" OFF)
option(GENERATE_SINGLE_HEADER   "run pcpp on include/ and produce single-header" OFF)

if(GENERATE_SINGLE_HEADER)
  set(WITH_SINGLE_HEADER ON CACHED)
endif()

check_cxx_compiler_flag(-Wl,-Bsymbolic HAS_BSYMBOLIC_COMPILERFLAG)
check_cxx_compiler_flag("-Xclang -march=native" HAS_XCLANG_COMPILERFLAG)
check_cxx_compiler_flag(-Wall HAS_WALL_COMPILERFLAG)
check_cxx_compiler_flag(-ggdb HAS_GGDB_COMPILERFLAG)

set(CXX11_CODE_EXAMPLE "\
#include <string>\n\
\
int main(int argc,char** argv){std::string msg;return msg.size();}")
set(CMAKE_REQUIRED_LIBRARIES -lc++ -lc++abi)
CHECK_CXX_SOURCE_COMPILES("${CXX11_CODE_EXAMPLE}" COMPILES_WITH_LIBCXX)
set(CMAKE_REQUIRED_LIBRARIES -lstdc++)
CHECK_CXX_SOURCE_COMPILES("${CXX11_CODE_EXAMPLE}" COMPILES_WITH_LIBSTDCXX)
unset(CMAKE_REQUIRED_LIBRARIES)
CHECK_CXX_SOURCE_COMPILES("${CXX11_CODE_EXAMPLE}" COMPILES_WITH_NO_EXTRAL)

check_cxx_compiler_flag(-lc++ HAS_LIBCXX_COMPILERFLAG)
check_cxx_compiler_flag(-lc++abi HAS_LIBCXXABI_COMPILERFLAG)
check_cxx_compiler_flag(-ggdb3 HAS_GGDB3_COMPILERFLAG)
check_cxx_compiler_flag(-O3 HAS_O3_COMPILERFLAG)
check_cxx_compiler_flag(/Oi HAS_OI_COMPILERFLAG)
check_cxx_compiler_flag(-Wno-overflow HAS_WNOOVERFLOW_COMPILERFLAG)


set(COMPASS_TARGET_NAME               ${PROJECT_NAME})
set(COMPASS_CONFIG_INSTALL_DIR        "lib/cmake/${PROJECT_NAME}"
  CACHE INTERNAL "")
set(COMPASS_INCLUDE_INSTALL_DIR       "include")
set(COMPASS_TARGETS_EXPORT_NAME       "${PROJECT_NAME}Targets")
set(COMPASS_CMAKE_CONFIG_TEMPLATE     "cmake/config.cmake.in")
set(COMPASS_CMAKE_CONFIG_DIR          "${CMAKE_CURRENT_BINARY_DIR}")
set(COMPASS_CMAKE_VERSION_CONFIG_FILE "${COMPASS_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(COMPASS_CMAKE_PROJECT_CONFIG_FILE "${COMPASS_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(COMPASS_CMAKE_PROJECT_TARGETS_FILE "${COMPASS_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")


if (NOT WITH_SINGLE_HEADER)
    set(COMPASS_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include")
    message(STATUS "Using the multi-header code from ${COMPASS_INCLUDE_BUILD_DIR}")
else()
    set(COMPASS_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/single_include")
    message(STATUS "Using the single-header code from ${COMPASS_INCLUDE_BUILD_DIR}")
endif()

add_library(${COMPASS_TARGET_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${COMPASS_TARGET_NAME} ALIAS ${COMPASS_TARGET_NAME})
target_include_directories(
    ${COMPASS_TARGET_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${COMPASS_INCLUDE_BUILD_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_definitions(${COMPASS_TARGET_NAME}
  INTERFACE LIBRARY_HEADER_ONLY
  INTERFACE cxx_std_11
  )

## ============== generate single-header ================
 if (${GENERATE_SINGLE_HEADER})
  find_program(PCPP NAMES pcpp PATH ${PCPP_PATH} PATH_SUFFIXES bin NO_DEFAULT_PATH)
  find_program(PCPP NAMES pcpp)
  if(EXISTS ${PCPP})
    message(STATUS "pcpp found at ${PCPP}")
    if(NOT EXISTS ${COMPASS_INCLUDE_BUILD_DIR})
      file(MAKE_DIRECTORY ${COMPASS_INCLUDE_BUILD_DIR})
      message("created ${COMPASS_INCLUDE_BUILD_DIR}")
    endif()

    execute_process(COMMAND ${PCPP} -o ${COMPASS_INCLUDE_BUILD_DIR}/compass.hpp --line-directive --passthru-defines --passthru-unfound-includes --passthru-unknown-exprs ${PROJECT_SOURCE_DIR}/include/compass.hpp
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      RESULT_VARIABLE PCPP_RESULT)
    if(${PCPP_RESULT} EQUAL 0)
      message(STATUS "Preprocessed ${PROJECT_SOURCE_DIR}/include/compass.hpp into ${COMPASS_INCLUDE_BUILD_DIR}/compass.hpp")
    else()
      message(FATAL_ERROR "Preprocessing ${PROJECT_SOURCE_DIR}/include/compass.hpp into ${COMPASS_INCLUDE_BUILD_DIR}/compass.hpp failed")
    endif()
  else()
    message(FATAL_ERROR "pcpp not found (${PCPP_PATH} ${PCPP_FOUND}), unable to continue in single-header configuration")
  endif()
endif()

#target_sources(compass INTERFACE include/compass.hpp)


IF(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "5.0")
    set(WITH_CXX11_ABI ON)
  endif()

  if(${WITH_CXX11_ABI})
    set(CXX11_ABI_VALUE 1)
  else()
    set(CXX11_ABI_VALUE 0)
  endif()

  target_compile_definitions(${COMPASS_TARGET_NAME} INTERFACE -D_GLIBCXX_USE_CXX11_ABI=${CXX11_ABI_VALUE})
  message(">> [${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}] adding -D_GLIBCXX_USE_CXX11_ABI=${CXX11_ABI_VALUE}")
endif()


IF(NOT WIN32)
  check_symbol_exists(__get_cpuid_max "cpuid.h" GET_CPUID_MAX_INSTRINSIC_EXISTS)
  check_symbol_exists(__cpuid_count "cpuid.h" GET_CPUID_COUNT_MACRO_INSTRINSIC_EXISTS)
ELSE()
  check_symbol_exists(__cpuid "intrin.h" GET_CPUID_INSTRINSIC_EXISTS)
ENDIF()

if(WITH_TESTS)
  add_subdirectory(tests)
  enable_testing()
  include("CTestLists.txt")
endif()

################################ EXPORT/INSTALL ################################
export(
  TARGETS ${COMPASS_TARGET_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${COMPASS_CMAKE_PROJECT_TARGETS_FILE}
  )
install(
  TARGETS ${COMPASS_TARGET_NAME}
  EXPORT ${PROJECT_NAME}Targets
  INCLUDES DESTINATION ${COMPASS_INCLUDE_INSTALL_DIR}
  )
install(
  EXPORT ${COMPASS_TARGETS_EXPORT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${COMPASS_CONFIG_INSTALL_DIR}
  )
install(DIRECTORY "${COMPASS_INCLUDE_BUILD_DIR}"
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
  )
