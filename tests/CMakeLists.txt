include(ExternalProject)

ExternalProject_Add(
    catch2
    PREFIX ${CMAKE_BINARY_DIR}/tests
    URL https://raw.githubusercontent.com/catchorg/Catch2/v2.2.2/single_include/catch.hpp
    URL_MD5 40b58ea3607594234e53e1748240876f
    DOWNLOAD_NO_EXTRACT TRUE
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
ExternalProject_Get_Property(catch2 DOWNLOAD_DIR)
set(CATCH2_HEADER_PATH ${DOWNLOAD_DIR})
message(STATUS "catch2 header file download to ${CATCH2_HEADER_PATH}")

add_library(catcho OBJECT catch.cpp)
target_include_directories(catcho PUBLIC ${CATCH2_HEADER_PATH})
add_dependencies(catcho catch2)

add_executable(test_compass_impl test_compass_impl.cpp $<TARGET_OBJECTS:catcho>)
target_include_directories(test_compass_impl PRIVATE ${CATCH2_HEADER_PATH} ${COMPASS_INCLUDE_BUILD_DIR})

add_executable(test_bitview test_bitview.cpp $<TARGET_OBJECTS:catcho>)
target_include_directories(test_bitview PRIVATE ${CATCH2_HEADER_PATH} ${COMPASS_INCLUDE_BUILD_DIR} )

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if(NOT "${COMPILES_WITH_NO_EXTRAL}")
    message(STATUS "detected malacious support of libc++/libstdc++")

    if(${COMPILES_WITH_LIBCXX})
      message(STATUS "adding c++ c++abi to test binary dependencies")

      target_link_libraries(test_compass_impl c++ c++abi)
      target_link_libraries(test_bitview c++ c++abi)
    else()

      if(${COMPILES_WITH_LIBSTDCXX})
        message(STATUS "adding stdc++ to test binary dependencies")

        target_link_libraries(test_compass_impl stdc++)
        target_link_libraries(test_bitview stdc++)
      endif()
    endif()
  endif()
endif()

#idea for generating test fixture at cmake-invocation
#Windows 7: use `wmic cpu GET Name` to obtain clearname of CPU model
#Linux    : use `lscpu` or `/proc/cpuinfo` to obtain more data about
#macOS    : not sure yet what to use

cmake_host_system_information(RESULT CURRENT_HOSTNAME QUERY HOSTNAME)

if(${CURRENT_HOSTNAME} MATCHES ".*(falcon2|talisker|schorle|scicomp-pc-3|recovery-station).*")

  add_executable(test_machine test_machine.cpp $<TARGET_OBJECTS:catcho>)
  target_include_directories(test_machine PRIVATE ${CATCH2_HEADER_PATH} ${COMPASS_INCLUDE_BUILD_DIR})

  add_executable(test_compass_sizes test_compass_sizes.cpp $<TARGET_OBJECTS:catcho>)
  target_include_directories(test_compass_sizes PRIVATE ${CATCH2_HEADER_PATH} ${COMPASS_INCLUDE_BUILD_DIR})

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND NOT "${COMPILES_WITH_NO_EXTRAL}")
    if(${COMPILES_WITH_LIBCXX})
      target_link_libraries(test_compass_sizes c++ c++abi)
      target_link_libraries(test_machine c++ c++abi)
    else()
      if(${COMPILES_WITH_LIBSTDCXX})
      target_link_libraries(test_compass_sizes stdc++)
      target_link_libraries(test_machine stdc++)
    endif()

    endif()


  endif()

endif()
