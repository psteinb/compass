include(ExternalProject)

ExternalProject_Add(
    catch2
    PREFIX ${CMAKE_BINARY_DIR}/tests
    URL https://raw.githubusercontent.com/catchorg/Catch2/v2.0.1/single_include/catch.hpp
    URL_MD5 9b3d2cb5c0f9532cddfbbfd0a622f0af
    DOWNLOAD_NO_EXTRACT TRUE
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
ExternalProject_Get_Property(catch2 DOWNLOAD_DIR)
set(CATCH2_HEADER_PATH ${DOWNLOAD_DIR})

message(STATUS "catch2 header file download to ${CATCH2_HEADER_PATH}")


cmake_host_system_information(RESULT CURRENT_HOSTNAME QUERY HOSTNAME)

add_library(catcho OBJECT catch.cpp)
target_include_directories(catcho PRIVATE ${CATCH2_HEADER_PATH})
add_dependencies(catcho catch2)

if(${CURRENT_HOSTNAME} MATCHES ".*(falcon2|talisker|schorle|scicomp-pc-3|recovery-station).*")
  add_executable(test_compass_impl test_compass_impl.cpp $<TARGET_OBJECTS:catcho>)
  target_include_directories(test_compass_impl PRIVATE ${PROJECT_SOURCE_DIR}/include ${CATCH2_HEADER_PATH})

  add_executable(test_compass_sizes test_compass_sizes.cpp $<TARGET_OBJECTS:catcho>)
  target_include_directories(test_compass_sizes PRIVATE ${PROJECT_SOURCE_DIR}/include ${CATCH2_HEADER_PATH})
endif()

#idea for generating test fixture at cmake-invocation
#Windows 7: use `wmic cpu GET Name` to obtain clearname of CPU model
#Linux    : use `lscpu` or `/proc/cpuinfo` to obtain more data about
#macOS    : not sure yet what to use

add_executable(test_bitview test_bitview.cpp $<TARGET_OBJECTS:catcho>)
target_include_directories(test_bitview PRIVATE ${PROJECT_SOURCE_DIR}/include ${CATCH2_HEADER_PATH})

### test single header

if(WITH_SINGLE_HEADER)
  find_program(PCPP NAME pcpp HINT ${PCPP_PATH})
  if(PCPP_FOUND OR EXISTS ${PCPP_PATH})
    add_custom_target(sh
      COMMAND pcpp --passthru-unfound-includes -I${PROJECT_SOURCE_DIR}/include/detail -o "${CMAKE_CURRENT_BINARY_DIR}/compass-sh.hpp" "${PROJECT_SOURCE_DIR}/include/compass.hpp"
      BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/compass-sh.hpp
      COMMENT "Preprocessing ${PROJECT_SOURCE_DIR}/include/compass.hpp into ${CMAKE_CURRENT_BINARY_DIR}/tests/compass-sh.hpp ..."
      USES_TERMINAL)
  else()
    message(WARNING "pcpp not found ${PCPP_PATH}")
  endif()

add_executable(test_single_header test_single_header.cpp $<TARGET_OBJECTS:catcho> ${CMAKE_CURRENT_BINARY_DIR}/compass-sh.hpp)
#add_dependencies(test_single_header sh)
target_include_directories(test_single_header PRIVATE ${PROJECT_BINARY_DIR}/tests ${CATCH2_HEADER_PATH})
endif()
