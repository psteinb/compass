INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

cmake_host_system_information(RESULT CURRENT_HOSTNAME QUERY HOSTNAME)

if(${CURRENT_HOSTNAME} MATCHES ".*(falcon2|schorle|scicomp-pc-3|recovery-station).*")
  add_executable(test_compass_impl test_compass_impl.cpp)
  target_link_libraries(test_compass_impl ${Boost_LIBRARIES})
elseif(${CURRENT_HOSTNAME} MATCHES "juronb.*")
  find_package(Threads REQUIRED)

  add_executable(test_power8_impl test_power8_impl.cpp)
  target_link_libraries(test_power8_impl ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif()
