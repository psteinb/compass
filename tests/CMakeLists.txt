
FIND_PACKAGE (Boost 1.50 COMPONENTS system filesystem unit_test_framework QUIET)
IF(DEFINED Boost_FOUND)

  include_directories(${Boost_INCLUDE_DIR})
  link_directories(${Boost_LIBRARY_DIR})
  MESSAGE("++ Boost libraries found  : ${Boost_LIBRARIES}")

else()
  MESSAGE("++ Boost not found ++ skipping tests!")
endif()



INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

cmake_host_system_information(RESULT CURRENT_HOSTNAME QUERY HOSTNAME)

if(${CURRENT_HOSTNAME} MATCHES ".*(falcon2|schorle|scicomp-pc-3|recovery-station).*")
  add_executable(test_compass_impl test_compass_impl.cpp)
  target_link_libraries(test_compass_impl ${Boost_LIBRARIES})
endif()

add_executable(test_bitview test_bitview.cpp)
target_link_libraries(test_bitview ${Boost_LIBRARIES})
