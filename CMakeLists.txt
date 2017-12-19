# cmake compatibility issues
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# project name
PROJECT(compass CXX)

# this project is C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckSymbolExists)

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

option(WITH_CXX11_ABI "enable _GLIBCXX_USE_CXX11_ABI in GCC 5.0+" ON)
option(WITH_TESTS     "enable unit tests" ON)

check_cxx_compiler_flag(-Wl,-Bsymbolic HAS_BSYMBOLIC_COMPILERFLAG)
check_cxx_compiler_flag("-Xclang -march=native" HAS_XCLANG_COMPILERFLAG)
check_cxx_compiler_flag(-Wall HAS_WALL_COMPILERFLAG)
check_cxx_compiler_flag(-ggdb HAS_GGDB_COMPILERFLAG)
check_cxx_compiler_flag(-ggdb3 HAS_GGDB3_COMPILERFLAG)
check_cxx_compiler_flag(-O3 HAS_O3_COMPILERFLAG)
check_cxx_compiler_flag(/Oi HAS_OI_COMPILERFLAG)
check_cxx_compiler_flag(-Wno-overflow HAS_WNOOVERFLOW_COMPILERFLAG)

IF(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "5.0")
    set(WITH_CXX11_ABI ON)
  endif()
  if(${WITH_CXX11_ABI})
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
    message(">> [GCC ${CMAKE_CXX_COMPILER_VERSION}] adding -D_GLIBCXX_USE_CXX11_ABI=1")
  else()
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
    message(">> [GCC ${CMAKE_CXX_COMPILER_VERSION}] adding -D_GLIBCXX_USE_CXX11_ABI=1")
  endif()
endif()

IF(NOT WIN32)
  # check_symbol_exists(__get_cpuid "cpuid.h" GET_CPUID_INSTRINSIC_EXISTS)
  # check_symbol_exists(__get_cpuid_count "cpuid.h" GET_CPUID_COUNT_INSTRINSIC_EXISTS)
  check_symbol_exists(__get_cpuid_max "cpuid.h" GET_CPUID_MAX_INSTRINSIC_EXISTS)
  check_symbol_exists(__cpuid_count "cpuid.h" GET_CPUID_COUNT_MACRO_INSTRINSIC_EXISTS)
ELSE()
  check_symbol_exists(__cpuid "intrin.h" GET_CPUID_INSTRINSIC_EXISTS)
  check_symbol_exists(__cpuidex "intrin.h" GET_CPUIDEX_INSTRINSIC_EXISTS)
ENDIF()

if(WITH_TESTS)
  add_definitions(-DBOOST_ALL_NO_LIB)
  set(Boost_USE_STATIC_LIBS       OFF)
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME    OFF)

  add_subdirectory(tests)
  enable_testing()
  include("CTestLists.txt")
endif()

################################ EXPORT/INSTALL ################################

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
)
