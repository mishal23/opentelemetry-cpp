include_directories(include)

add_library(opentelemetry_exporter_etw_provider src/etw_provider_exporter.cc)
add_library(opentelemetry_exporter_etw_tracer src/etw_tracer_exporter.cc)
add_library(opentelemetry_exporter_etw_logger src/etw_logger_exporter.cc)

if(BUILD_TESTING)
  add_executable(etw_provider_test test/etw_provider_test.cc)
  add_executable(etw_tracer_test test/etw_tracer_test.cc)

  target_link_libraries(
    etw_provider_test ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
    opentelemetry_exporter_etw_provider)

  target_link_libraries(
    etw_tracer_test ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
    opentelemetry_exporter_etw_tracer)

  target_link_libraries(
    etw_logger_test ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
    opentelemetry_exporter_etw_logger)

  gtest_add_tests(
    TARGET etw_provider_test
    TEST_PREFIX exporter.
    TEST_LIST etw_provider_test)
  gtest_add_tests(
    TARGET etw_tracer_test
    TEST_PREFIX exporter.
    TEST_LIST etw_tracer_test)
  gtest_add_tests(
    TARGET etw_logger_test
    TEST_PREFIX exporter.
    TEST_LIST etw_logger_test)
endif() # BUILD_TESTING
