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

check_cxx_compiler_flag(-Wl,-Bsymbolic HAS_BSYMBOLIC_COMPILERFLAG)
check_cxx_compiler_flag("-Xclang -march=native" HAS_XCLANG_COMPILERFLAG)
check_cxx_compiler_flag(-Wall HAS_WALL_COMPILERFLAG)
check_cxx_compiler_flag(-ggdb HAS_GGDB_COMPILERFLAG)
check_cxx_compiler_flag(-ggdb3 HAS_GGDB3_COMPILERFLAG)
check_cxx_compiler_flag(-O3 HAS_O3_COMPILERFLAG)
check_cxx_compiler_flag(/Oi HAS_OI_COMPILERFLAG)
check_cxx_compiler_flag(-Wno-overflow HAS_WNOOVERFLOW_COMPILERFLAG)



IF(NOT WIN32)
  # check_symbol_exists(__get_cpuid "cpuid.h" GET_CPUID_INSTRINSIC_EXISTS)
  # check_symbol_exists(__get_cpuid_count "cpuid.h" GET_CPUID_COUNT_INSTRINSIC_EXISTS)
  check_symbol_exists(__get_cpuid_max "cpuid.h" GET_CPUID_MAX_INSTRINSIC_EXISTS)
  check_symbol_exists(__cpuid_count "cpuid.h" GET_CPUID_COUNT_MACRO_INSTRINSIC_EXISTS)
ELSE()
  check_symbol_exists(__cpuid "intrin.h" GET_CPUID_INSTRINSIC_EXISTS)
  check_symbol_exists(__cpuidex "intrin.h" GET_CPUIDEX_INSTRINSIC_EXISTS)
  add_definitions(-DBOOST_ALL_NO_LIB)

  set(Boost_USE_STATIC_LIBS       OFF)
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME    OFF)

ENDIF()

#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

FIND_PACKAGE (Boost 1.50 COMPONENTS system filesystem unit_test_framework QUIET)
IF(DEFINED Boost_FOUND)

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
      message(">> [gnu compiler detected] CXX11_ABI enabled.")
  endif()

  include_directories(${Boost_INCLUDE_DIR})
  link_directories(${Boost_LIBRARY_DIR})
  MESSAGE("++ Boost libraries found  : ${Boost_LIBRARIES}")
  ADD_SUBDIRECTORY(tests)
  enable_testing()
  include("CTestLists.txt")
else()
  MESSAGE("++ Boost not found ++ skipping tests!")
endif()

################################ EXPORT/INSTALL ################################

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
)
