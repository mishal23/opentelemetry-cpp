include(GoogleTest)

foreach(testname kv_properties_test string_util_test)
  add_executable(${testname} "${testname}.cc")
  target_link_libraries(
    ${testname} ${GTEST_BOTH_LIBRARIES} ${CORE_RUNTIME_LIBS}
    ${CMAKE_THREAD_LIBS_INIT} opentelemetry_api)
  gtest_add_tests(
    TARGET ${testname}
    TEST_PREFIX common.
    TEST_LIST ${testname})
endforeach()

add_executable(spinlock_benchmark spinlock_benchmark.cc)
target_link_libraries(spinlock_benchmark benchmark::benchmark
                      ${CMAKE_THREAD_LIBS_INIT} opentelemetry_api)
