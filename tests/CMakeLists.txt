INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

add_executable(test_compass_impl test_compass_impl.cpp)
target_link_libraries(test_compass_impl ${Boost_LIBRARIES})
